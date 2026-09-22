//
//  Copyright 2015-2026
//  Author(s): Bart Gysens <gysens.bart@gmail.com>
//
//  This file is part of Steel.
//
//  Steel is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Steel is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Steel. If not, see <http://www.gnu.org/licenses/>.
//


#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include "utils/SysLog.h"
#include "actions/Rival100Actions.h"


using namespace steel::config;
using namespace steel::context;
using namespace steel::device;
using namespace steel::utils;


namespace steel
{
    namespace actions
    {
        Rival100Actions::Rival100Actions( const SteelConfig& config, const std::vector<HidDeviceInfo>& devices )
            : IActions{ devices }
            , _config( *dynamic_cast<const Rival100Config*>( config.devices().at( "rival-100" ).get() ) ) // no uniform initialization because of gcc 4.8 bug
            , _device{ std::unique_ptr<Rival100>( nullptr ) }
        {

            for ( auto pos = _devices.begin(); pos != _devices.end(); ++pos )
            {
                if ( pos->type() == HidDeviceInfo::Type::Rival100 )
                {
                    _device = std::unique_ptr<Rival100>( new Rival100( *pos ) );
                    break;
                }
            }
        }


        int Rival100Actions::exec( int argc, char* argv[] )
        {
            Rival100Context context( _config.deviceName() );
            int result = context.create( argc, argv );

            if ( result == 0 )
            {
                switch ( context.command() )
                {
                    case Rival100Context::Command::Help :
                        std::cout << context.syntax( 0 ) << std::endl;
                        return 0;

                    case Rival100Context::Command::Active :
                        return _execActive( context );

                    case Rival100Context::Command::Profile :
                        return _execProfile( context );

                    default :
                        return _error( -102, "unsupported command \'%d\'", context.command() );
                }
            }

            return result;
        }

        int Rival100Actions::_execActive( const Rival100Context& context )
        {
            (void) context;
            return _execProfile( _config.active() );
        }


        int Rival100Actions::_execProfile( const Rival100Context& context )
        {
            auto profiles = _config.profiles();

            for ( auto pos = profiles.begin(); pos != profiles.end(); ++pos )
            {
                if ( context.profile() == pos->name() )
                    return _execProfile( *pos );
            }

            return _error( -200, "profile \'%s\' not found in configuration", context.profile().c_str() );
        }


        int Rival100Actions::_execProfile( const Rival100Profile& profile )
        {
            if ( _device.get() == nullptr )
                return _error( -301, "device not found" );

            int result;

            if (   ( ( result = _device.get()->setSensitivity( profile.cpi1(), profile.cpi2() ) ) != 0 )
                || ( ( result = _device.get()->setPollingRate( profile.pollingRate() ) ) != 0 )
                || ( ( result = _device.get()->setColor( profile.color() ) ) != 0 )
                || ( ( result = _device.get()->setBreathe( profile.breathe() ) ) != 0 ) )
                return result;

            return 0;
        }


        int Rival100Actions::_error( int result, const char* fmt, ... )
        {
            const int error = -11000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): %s: %s", result += error, _config.deviceName().c_str(), buffer.data() );
            std::fprintf( stderr, "\nerror (%d): %s: %s\n\n", result, _config.deviceName().c_str(), buffer.data() );
            return result;
        }
    }
}
