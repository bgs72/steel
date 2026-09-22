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


#include <fstream>
#include <sstream>
#include "utils/Lookup.h"
#include "utils/SysLog.h"
#include "utils/Utils.h"
#include "config/MsiKeyboardConfig.h"
#include "config/MsiKeyboardProfile.h"
#include "config/Rival100Config.h"
#include "config/Rival100Profile.h"
#include "parser/IDeviceParser.h"
#include "parser/MsiKeyboardParser.h"
#include "parser/Rival100Parser.h"
#include "parser/SteelParser.h"


using namespace steel::config;
using namespace steel::device;
using namespace steel::parser;
using namespace steel::utils;


namespace steel
{
    namespace parser
    {
        std::vector<std::tuple<IDeviceConfig::DeviceType,std::string>> SteelParser::_deviceTypes
            { std::make_tuple( IDeviceConfig::DeviceType::MsiKeyboard, "msi-keyboard" )
            , std::make_tuple( IDeviceConfig::DeviceType::Rival100, "rival-100" ) };


        SteelParser::SteelParser( const std::string& fpath )
            : _fpath{ fpath }
            , _line{}
            , _lineNumber{ -1 }
        {
        }


        int SteelParser::parse( SteelConfig& config )
        {
            try
            {
                std::ifstream file( _fpath );

                if ( file.is_open() )
                {
                    for ( _lineNumber = 1; std::getline( file, _line ); ++_lineNumber )
                    {
                        trim( _line );

                        if (   ( _line.size() == 0 )
                            || ( _line.at( 0 ) == '#' ) )
                            continue;

                        if ( _line.at( 0 ) == '[' )
                        {
                            auto pos = _line.find( ']', 1 );
                            if ( pos == std::string::npos )
                                return _error( -205, "open bracket without close bracket in \'%s\'", _line.c_str() );

                            auto deviceName = _line.substr( 1, pos - 1 );
                            IDeviceConfig::DeviceType deviceType;
                            if ( !lookup( _deviceTypes, deviceName, deviceType ) )
                                return _error( -204, "unknown device type in \'%s\'", _line.c_str() );

                            std::shared_ptr<IDeviceConfig> deviceConfig;
                            std::unique_ptr<IDeviceParser> deviceParser;

                            switch ( deviceType )
                            {
                                case IDeviceConfig::DeviceType::MsiKeyboard :
                                    deviceConfig = std::make_shared<MsiKeyboardConfig>( deviceName );
                                    deviceParser = std::unique_ptr<MsiKeyboardParser>( new MsiKeyboardParser( file, _lineNumber, _fpath ) );
                                    break;

                                case IDeviceConfig::DeviceType::Rival100 :
                                    deviceConfig = std::make_shared<Rival100Config>( deviceName );
                                    deviceParser = std::unique_ptr<Rival100Parser>( new Rival100Parser( file, _lineNumber, _fpath ) );
                                    break;

                                default:
                                    // do nothing
                                    break;
                            }

                            auto error = deviceParser->parse( deviceConfig );
                            if ( error != 0 )
                                return error;

                            config._devices.insert( std::make_pair( deviceConfig->deviceName(), deviceConfig ) );
                        }
                        else
                        {
                            return _error( -203, "unexpected line \'%s\'", _line.c_str() );
                        }
                    }
                }
                else
                {
                    return _error( -202, "file not found" );
                }
            }
            catch ( const std::exception& e )
            {
                return _error( -201, "exception \'%s\'", e.what() );
            }

            return 0;
        }


        int SteelParser::_error( int result, const char* fmt, ... )
        {
            const int error = -60000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): at line %d in file %s: %s", result += error, _lineNumber, _fpath.c_str(), buffer.data() );
            std::fprintf( stderr, "\nerror (%d): at line %d in file %s: %s\n\n", result, _lineNumber, _fpath.c_str(), buffer.data() );
            return result;
        }
    }
}
