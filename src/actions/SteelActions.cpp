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
#include <chrono>
#include <iomanip>
#include <iostream>
#include "config/SteelConfig.h"
#include "parser/SteelParser.h"
#include "context/SteelContext.h"
#include "utils/SysLog.h"
#include "actions/MsiKeyboardActions.h"
#include "actions/Rival100Actions.h"
#include "actions/SteelActions.h"


using namespace steel::config;
using namespace steel::context;
using namespace steel::device;
using namespace steel::parser;
using namespace steel::utils;


namespace steel
{
    namespace actions
    {
        std::string SteelActions::_version( "0.1.0" );


        SteelActions::SteelActions()
            : IActions( IHidDevice::enumerate() )
        {
        }


        int SteelActions::exec( int argc, char* argv[] )
        {
            SteelContext context;
            int result = context.create( argc, argv );

            if ( result == 0 )
            {
                SteelConfig config;
                SteelParser parser( "/etc/steel.conf" );

                switch ( context.command() )
                {
                    case SteelContext::Command::Help :
                        return _execHelp( context );

                    case SteelContext::Command::Query :
                        return _execQuery();

                    case SteelContext::Command::Version :
                        return _execVersion();

                    case SteelContext::Command::Active :
                    case SteelContext::Command::Profile :
                        if ( ( result = parser.parse( config ) ) != 0 )
                            return result;
                        return _execAllDevices( argc, argv, config );

                    case SteelContext::Command::MsiKeyboard :
                        if ( ( result = parser.parse( config ) ) != 0 )
                            return result;
                        return _execMsiKeyboard( argc, argv, config );

                    case SteelContext::Command::Rival :
                        if ( ( result = parser.parse( config ) ) != 0 )
                            return result;
                        return _execRival100( argc, argv, config );

                    default :
                        return _error( -101, "unsupported command \'%d\'", context.command() );
                }
            }

            return result;
        }


        int SteelActions::_execHelp( const SteelContext& context )
        {
            std::cout << context.syntax( 0 ) << std::endl;
            return 0;
        }


        int SteelActions::_execQuery()
        {
            std::cout << std::endl
                      << "Enumerating hid devices:" << std::endl;

            std::for_each( _devices.begin(), _devices.end(), []( const HidDeviceInfo object )
            {
                std::cout << object .toString( 2 );
            } );

            std::cout << std::endl;
            return 0;
        }


        int SteelActions::_execVersion()
        {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t( now );
            auto lt = std::localtime( &time_t );

            std::cout << "steel " << _version << ", copyright 2015-" << std::put_time( lt, "%Y" ) << std::endl
                      << std::endl
                      << "Author(s):" << std::endl
                      << "Bart Gysens <gysens.bart@gmail.com>" << std::endl
                      << std::endl
                      << "Steel is free software: you can redistribute it and/or modify" << std::endl
                      << "it under the terms of the GNU General Public License as published by" << std::endl
                      << "the Free Software Foundation, either version 3 of the License, or" << std::endl
                      << "(at your option) any later version." << std::endl
                      << std::endl
                      << "Steel is distributed in the hope that it will be useful," << std::endl
                      << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl
                      << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
                      << "GNU General Public License for more details." << std::endl
                      << std::endl
                      << "You should have received a copy of the GNU General Public License" << std::endl
                      << "along with Steel. If not, see <http://www.gnu.org/licenses/>." << std::endl
                      << std::endl;
            return 0;
        }


        int SteelActions::_execAllDevices( int argc, char* argv[], const SteelConfig& config )
        {
            int error = 0;
            int result = 0;

            char* argv2[argc+1];
            argv2[0] = argv[0];
            for ( int i=1; i<argc; ++i )
                argv2[i+1] = argv[i];

            for ( std::vector<HidDeviceInfo>::const_iterator pos = _devices.begin(); pos != _devices.end(); ++pos )
            {
                switch ( pos->type() )
                {
                    case HidDeviceInfo::Type::MsiKeyboard :
                    {
                        char device[] = "msi-keyboard";
                        argv2[1] = device;
                        if ( ( result = _execMsiKeyboard( argc+1, argv2, config ) ) != 0 )
                            error = result;
                        break;
                    }

                    case HidDeviceInfo::Type::Rival100 :
                    {
                        char device[] = "rival-100";
                        argv2[1] = device;
                        if ( ( result = _execRival100( argc+1, argv2, config ) ) != 0 )
                            error = result;
                        break;
                    }

                    default:
                        // do nothing.
                        break;
                }
            }

            return error;
        }


        int SteelActions::_execMsiKeyboard( int argc, char* argv[], const SteelConfig& config )
        {
            MsiKeyboardActions actions( config, _devices );
            return actions.exec( argc, argv );

        }


        int SteelActions::_execRival100( int argc, char* argv[], const SteelConfig& config )
        {
            Rival100Actions actions( config, _devices );
            return actions.exec( argc, argv );
        }


        int SteelActions::_error( int result, const char* fmt, ... )
        {
            const int error = -12000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): %s", result += error, buffer.data() );
            std::fprintf( stderr, "\nerror (%d): %s\n\n", result, buffer.data() );
            return result;
        }
    }
}
