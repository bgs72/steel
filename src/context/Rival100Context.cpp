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
#include <sstream>
#include "utils/SysLog.h"
#include "context/Rival100Context.h"


using namespace steel::utils;


namespace steel
{
    namespace context
    {
        std::vector<std::tuple<Rival100Context::Command,std::string,std::string>> Rival100Context::_commands =
        { std::make_tuple( Rival100Context::Command::Help, "--help", "show this information" )
        , std::make_tuple( Rival100Context::Command::Active, "--active", "use profile that is marked active in configuration" )
        , std::make_tuple( Rival100Context::Command::Profile, "--profile", "use profile with given name" ) };


        Rival100Context::Rival100Context( const std::string& deviceName )
            : IContext{ deviceName }
            , _command{ Command::Active }
            , _profile{}
        {
        }


        int Rival100Context::create( int argc, char* argv[] )
        {
            _command = Command::Invalid;
            _profile.clear();

            if ( argc < 3 )
                return _error( -105, "no option specified, use --help for syntax help" );

            if ( deviceName() == argv[1] )
            {
                if ( argc > 2 )
                {
                    auto pos = std::find_if( _commands.begin(), _commands.end(), [argv]( const std::tuple<Command,std::string,std::string>& object )
                    {
                        auto command = std::get<1>( object );
                        return ( command.compare( 0, command.size(), argv[2] ) == 0 );
                    } );

                    if ( pos != _commands.end() )
                        _command = std::get<0>( *pos );
                    else
                        return _error( -104, "undefined command \'%s\'", argv[2] );
                }
            }
            else
                return _error( -103, "device mismatch \'%s\'", argv[1] );

            switch ( _command )
            {
                case Command::Help :
                    if ( argc > 3 )
                        return _error( -102, "invalid argument data for command \'%s\'", std::get<1>( _commands[2] ).c_str() );
                    break;

                case Command::Profile :
                    if ( argc == 4 )
                        _profile = argv[3];
                     else
                        return _error( -101, "invalid argument data for command \'%s\'", std::get<1>( _commands[1] ).c_str() );
                    break;

                case Command::Active :
                default:
                    if (   ( argc > 3 )
                        || (   ( argc > 2 )
                            && ( std::get<1>( _commands[1] ) != argv[2] ) ) )
                        return _error( -100, "invalid argument data for command \'%s\'", std::get<1>( _commands[0] ).c_str() );
                    break;
            }

            return 0;
        }


        std::string Rival100Context::syntax( int indent ) const
        {
            const int align = 30;
            std::string fill( indent, ' ' );
            std::string syntax( "syntax: " );
            std::string options( "options: " );
            std::string name( " <name>" );
            std::ostringstream sstr;

            sstr << std::endl
                 << fill << syntax << "steel " << deviceName() << " <options>" << std::endl
                 << std::endl
                 << fill << std::string( syntax.size(), ' ' ) << options << std::endl;

            for ( auto pos = _commands.begin(); pos != _commands.end(); ++pos )
            {
                sstr << fill
                     << std::string( syntax.size(), ' ' )
                     << std::get<1>( *pos );

                if ( std::get<0>( *pos ) == Command::Profile )
                    sstr << name;


                sstr << std::string( align - syntax.size() - std::get<1>( *pos ).size() - (std::get<0>( *pos ) == Command::Profile ? name.size() : 0), ' ' )
                      << std::get<2>( *pos )
                      << std::endl;
            }

            return sstr.str();
        }


        Rival100Context::Command Rival100Context::command() const
        {
            return _command;
        }


        const std::string& Rival100Context::profile() const
        {
            return _profile;
        }


        int Rival100Context::_error( int result, const char* fmt, ... )
        {
            const int error = -31000;
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
