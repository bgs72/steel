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


#include "config/MsiKeyboardConfig.h"
#include "utils/Lookup.h"
#include "utils/Utils.h"
#include "parser/MsiKeyboardParser.h"


using namespace steel::config;
using namespace steel::device;
using namespace steel::utils;


namespace steel
{
    namespace parser
    {
        std::vector<const char*> MsiKeyboardParser::_keywords
            { "profile"
            , "active" };

        std::vector<std::tuple<MsiKeyboard::Mode,std::string>> MsiKeyboardParser::_modes
            { std::make_tuple( MsiKeyboard::Mode::Disable, "disable" )
            , std::make_tuple( MsiKeyboard::Mode::Normal, "normal" )
            , std::make_tuple( MsiKeyboard::Mode::Game, "game" )
            , std::make_tuple( MsiKeyboard::Mode::Breathe, "breathe" )
            , std::make_tuple( MsiKeyboard::Mode::Wave, "wave" )
            , std::make_tuple( MsiKeyboard::Mode::BiColor, "bicolor" ) };

        std::vector<std::tuple<MsiKeyboard::Intensity,std::string>> MsiKeyboardParser::_intenseties
            { std::make_tuple( MsiKeyboard::Intensity::Low, "low" )
            , std::make_tuple( MsiKeyboard::Intensity::Medium, "medium" )
            , std::make_tuple( MsiKeyboard::Intensity::High, "high" )
            , std::make_tuple( MsiKeyboard::Intensity::Max, "max" ) };

        std::vector<std::tuple<MsiKeyboard::Color,std::string>> MsiKeyboardParser::_colors
            { std::make_tuple( MsiKeyboard::Color::Black, "black" )
            , std::make_tuple( MsiKeyboard::Color::Red, "red" )
            , std::make_tuple( MsiKeyboard::Color::Orange, "orange" )
            , std::make_tuple( MsiKeyboard::Color::Yellow, "yellow" )
            , std::make_tuple( MsiKeyboard::Color::Green, "green" )
            , std::make_tuple( MsiKeyboard::Color::Sky, "sky" )
            , std::make_tuple( MsiKeyboard::Color::Blue, "blue" )
            , std::make_tuple( MsiKeyboard::Color::Purple, "purple" )
            , std::make_tuple( MsiKeyboard::Color::White, "white" ) };


        MsiKeyboardParser::MsiKeyboardParser( std::ifstream& stream, int& lineNumber, const std::string& fpath )
            : IDeviceParser{ stream, lineNumber, fpath }
        {
        }


        MsiKeyboardParser::~MsiKeyboardParser()
        {
        }


        int MsiKeyboardParser::parse( std::shared_ptr<config::IDeviceConfig> config )
        {
            MsiKeyboardConfig* msiKeyboardConfig = dynamic_cast<MsiKeyboardConfig*>( config.get() );
            if ( msiKeyboardConfig == nullptr )
                return _error( -100, "invalid object" );

            std::string line;
            while ( _getline( line ) )
            {
                auto pos = std::find_if( _keywords.begin(), _keywords.end(), [line]( const char* object )->bool
                {
                    std::string tag = object;
                    return line.compare( 0, tag.size(), tag ) == 0;
                } );

                if ( pos == _keywords.end() )
                    return _error( -101, "unknown keyword in \'%s\'", line.c_str() );

                if ( *pos == _keywords.at( 0 ) )
                {
                    // profile keyword
                    MsiKeyboardProfile msiKeyboardProfile;
                    bool done = false;
                    int fieldNumber = 0;

                    for ( auto bgn = line.find_first_of( "=", 0 ), end = bgn; bgn != std::string::npos && !done; ++fieldNumber )
                    {
                        end = line.find_first_of( ",", ++bgn );
                        auto field( trim_copy( line.substr( bgn, end - bgn ) ) );
                        bgn = end;

                        switch ( fieldNumber )
                        {
                            case 0 :    // name
                                msiKeyboardProfile._name = field;
                                break;

                            case 1 :    // mode
                                if ( !lookup( _modes, field, msiKeyboardProfile._mode ) )
                                    return _error( -102, "undefined mode \'%s\'", field.c_str() );
                                done = ( msiKeyboardProfile._mode == MsiKeyboard::Mode::Disable );
                                break;

                            case 2 :    // intensity
                                if ( !lookup( _intenseties, field, msiKeyboardProfile._intensity ) )
                                    return _error( -103, "undefined intensity \'%s\'", field.c_str() );
                                break;

                            case 3 :    // colors
                            {
                                size_t from = 0;
                                auto to = field.find_first_of( ":" );
                                auto color( trim_copy( field.substr( from, to - from ) ) );

                                if ( !lookup( _colors, color, msiKeyboardProfile._color1 ) )
                                    return _error( -104, "undefined color \'%s\'", field.c_str() );

                                if ( to != std::string::npos )
                                {
                                    to = field.find_first_of( ":", ++(from = to) );
                                    color = trim_copy( field.substr( from, to - from ) );

                                    if ( !lookup( _colors, color, msiKeyboardProfile._color2 ) )
                                        return _error( -105, "undefined color \'%s\'", field.c_str() );
                                }

                                if ( to != std::string::npos )
                                {
                                    to = field.find_first_of( ":", ++(from = to) );
                                    color = trim_copy( field.substr( from, to - from ) );

                                    if ( !lookup( _colors, color, msiKeyboardProfile._color3 ) )
                                        return _error( -106, "undefined color \'%s\'", field.c_str() );
                                }

                                done = ( end == std::string::npos );
                                break;
                            }

                            case 4:     // speed
                                try
                                {
                                    msiKeyboardProfile._speed = std::stoi( field );
                                }
                                catch ( const std::exception& e )
                                {
                                    return _error( -107, "speed is not an integer value \'%s\'", field.c_str() );
                                }

                                done = true;
                                break;

                            default:
                                return _error( -108, "too many fields in \'%s\'", line.c_str() );
                        }

                        if ( done )
                        {
                            msiKeyboardConfig->_profiles.push_back( msiKeyboardProfile );
                        }
                    }

                    if ( !done )
                        return _error( -109, "missing fields in \'%s\'", line.c_str() );
                }
                else if ( *pos == _keywords.at( 1 ) )
                {
                    // active keyword
                    auto bgn = line.find_first_of( "=", 0 );
                    auto profile( trim_copy( line.substr( ++bgn ) ) );
                    auto profiles = msiKeyboardConfig->profiles();
                    auto pos = std::find_if( profiles.begin(), profiles.end(), [profile]( const MsiKeyboardProfile& object )->bool
                    {
                        if ( profile == object.name() )
                            return true;
                        return false;
                    } );

                    if ( pos == profiles.end() )
                        return _error( -110, "specified active profile is not found \'%s\'", line.c_str() );

                    msiKeyboardConfig->_active = *pos;
                }
            }

            return 0;
        }
    }
}
