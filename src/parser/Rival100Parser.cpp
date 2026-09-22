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


#include "config/Rival100Config.h"
#include "utils/Lookup.h"
#include "utils/Utils.h"
#include "parser/Rival100Parser.h"


using namespace steel::config;
using namespace steel::device;
using namespace steel::utils;


namespace steel
{
    namespace parser
    {
        std::vector<const char*> Rival100Parser::_keywords
            { "profile"
            , "active" };

        std::vector<std::tuple<Rival100::RGB,std::string>> Rival100Parser::_colors
            { std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Black ), "black" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Red ), "red" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Orange ), "orange" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Yellow ), "yellow" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Green ), "green" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Sky ), "sky" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Blue ), "blue" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::Purple ), "purple" )
            , std::make_tuple( Rival100::RGB::fromColor( Rival100::RGB::White ), "white" ) };

        std::vector<std::tuple<Rival100::Breathe,std::string>> Rival100Parser::_breathes
            { std::make_tuple( Rival100::Breathe::Off, "off" )
            , std::make_tuple( Rival100::Breathe::Slow, "slow" )
            , std::make_tuple( Rival100::Breathe::Medium, "medium" )
            , std::make_tuple( Rival100::Breathe::Fast, "fast" ) };

        std::vector<std::tuple<Rival100::PollingRate,std::string>> Rival100Parser::_pollingRates
            { std::make_tuple( Rival100::PollingRate::Low, "low" )
            , std::make_tuple( Rival100::PollingRate::Medium, "medium" )
            , std::make_tuple( Rival100::PollingRate::High, "high" )
            , std::make_tuple( Rival100::PollingRate::Max, "max" ) };


        Rival100Parser::Rival100Parser( std::ifstream& stream, int& lineNumber, const std::string& fpath )
            : IDeviceParser{ stream, lineNumber, fpath }
        {
        }


        Rival100Parser::~Rival100Parser()
        {
        }


        int Rival100Parser::parse( std::shared_ptr<config::IDeviceConfig> config )
        {
            Rival100Config* rival100Config = dynamic_cast<Rival100Config*>( config.get() );
            if ( rival100Config == nullptr )
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
                    Rival100Profile rival100Profile;
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
                                rival100Profile._name = field;
                                break;

                            case 1 :    // color
                                if (   ( Rival100::RGB::fromString( field.c_str(), rival100Profile._color ) != 0 )
                                    && ( !lookup( _colors, field, rival100Profile._color ) ) )
                                    return _error( -102, "undefined color \'%s\'", field.c_str() );
                                break;

                            case 2:     // breathe
                                if ( !lookup( _breathes, field, rival100Profile._breathe ) )
                                    return _error( -103, "undefined breathe \'%s\'", field.c_str() );
                                break;

                            case 3 :    // cpi1
                                try
                                {
                                    rival100Profile._cpi1 = std::stoi( field );
                                }
                                catch ( const std::exception& e )
                                {
                                    return _error( -105, "cpi1 value is not integer \'%s\'", field.c_str() );
                                }
                                break;

                            case 4:     // cpi2
                                try
                                {
                                    rival100Profile._cpi2 = std::stoi( field );
                                }
                                catch ( const std::exception& e )
                                {
                                    return _error( -106, "cpi2 value is not integer \'%s\'", field.c_str() );
                                }
                                break;

                            case 5:     //  pollingrate
                                if ( !lookup( _pollingRates, field, rival100Profile._pollingRate ) )
                                    return _error( -107, "undefined polling rate \'%s\'", field.c_str() );
                                done = true;
                                break;

                            default:
                                return _error( -108, "too many fields in \'%s\'", line.c_str() );
                        }

                        if ( done )
                        {
                            rival100Config->_profiles.push_back( rival100Profile );
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
                    auto profiles = rival100Config->profiles();
                    auto pos = std::find_if( profiles.begin(), profiles.end(), [profile]( const Rival100Profile& object )->bool
                    {
                        if ( profile == object.name() )
                            return true;
                        return false;
                    } );

                    if ( pos == profiles.end() )
                    {
                        return _error( -110, "specified active profile is not found \'%s\'", line.c_str() );
                    }

                    rival100Config->_active = *pos;
                }
            }

            return 0;
        }
    }
}
