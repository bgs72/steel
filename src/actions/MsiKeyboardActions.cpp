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
#include "actions/MsiKeyboardActions.h"


using namespace steel::config;
using namespace steel::context;
using namespace steel::device;
using namespace steel::utils;


namespace steel
{
    namespace actions
    {
        MsiKeyboardActions::MsiKeyboardActions( const SteelConfig& config, const std::vector<HidDeviceInfo>& devices )
            : IActions{ devices }
            , _config{ *dynamic_cast<const MsiKeyboardConfig*>( config.devices().at( "msi-keyboard" ).get() ) }
            , _device{ std::unique_ptr<MsiKeyboard>( nullptr ) }
        {

            for ( auto pos = _devices.begin(); pos != _devices.end(); ++pos )
            {
                if ( pos->type() == HidDeviceInfo::Type::MsiKeyboard )
                {
                    _device = std::unique_ptr<MsiKeyboard>( new MsiKeyboard( *pos ) );
                    break;
                }
            }
        }


        int MsiKeyboardActions::exec( int argc, char* argv[] )
        {
            MsiKeyboardContext context( _config.deviceName() );
            int result = context.create( argc, argv );

            if ( result == 0 )
            {
                switch ( context.command() )
                {
                    case MsiKeyboardContext::Command::Help :
                        std::cout << context.syntax( 0 ) << std::endl;
                        return 0;

                    case MsiKeyboardContext::Command::Active :
                        return _execActive( context );

                    case MsiKeyboardContext::Command::Profile :
                        return _execProfile( context );

                    default :
                        return _error( -102, "unsupported command \'%d\'", context.command() );
                }
            }

            return result;
        }


        int MsiKeyboardActions::_execActive( const MsiKeyboardContext& context )
        {
            (void) context;
            return _execProfile( _config.active() );
        }


        int MsiKeyboardActions::_execProfile( const MsiKeyboardContext& context )
        {
            auto profiles = _config.profiles();

            for ( auto pos = profiles.begin(); pos != profiles.end(); ++pos )
            {
                if ( context.profile() == pos->name() )
                    return _execProfile( *pos );
            }

            return _error( -200, "profile \'%s\' not found in configuration", context.profile().c_str() );
        }


        int MsiKeyboardActions::_execProfile( const MsiKeyboardProfile& profile )
        {
            if ( _device.get() == nullptr )
                return _error( -301, "device not found" );

            typedef MsiKeyboard::Color Colors[];

            switch ( profile.mode() )
            {
                case MsiKeyboard::Mode::Disable :
                    return _device.get()->disable();

                case MsiKeyboard::Mode::Normal :
                    return _device.get()->normal( profile.intensity(), std::move( Colors{ profile.color1(), profile.color2(), profile.color3() } ) );

                case MsiKeyboard::Mode::Game :
                    return _device.get()->gaming( profile.intensity(), profile.color1() );

                case MsiKeyboard::Mode::Breathe :
                    return _device.get()->breathing( profile.intensity(), std::move( Colors{ profile.color1(), profile.color2(), profile.color3() } ), profile.speed() );

                case MsiKeyboard::Mode::Wave :
                    return _device.get()->wave( profile.intensity(), std::move( Colors{ profile.color1(), profile.color2(), profile.color3() } ), profile.speed() );

                case MsiKeyboard::Mode::BiColor :
                    return _device.get()->bicolor( profile.intensity(), std::move( Colors{ profile.color1(), profile.color2() } ), profile.speed() );

                default:
                    return _error( -300, "undefined mode \'%d\'", static_cast<int>( profile.mode() ) );
            }
        }


        int MsiKeyboardActions::_error( int result, const char* fmt, ... )
        {
            const int error = -10000;
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
