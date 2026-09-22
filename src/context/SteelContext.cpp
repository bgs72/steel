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
#include "context/SteelContext.h"


using namespace steel::utils;


namespace steel
{
    namespace context
    {
        std::vector<std::tuple<SteelContext::Command,std::string,std::string>> SteelContext::_commands =
        { std::make_tuple( SteelContext::Command::Help, "--help", "show this information" )
          , std::make_tuple( SteelContext::Command::Active, "--active", "use profile that is marked active in configuration for supported hid devices" )
          , std::make_tuple( SteelContext::Command::Profile, "--profile", "use profile with given name for supported hid devices" )
        , std::make_tuple( SteelContext::Command::Query, "--query", "display info on available hid devices" )
        , std::make_tuple( SteelContext::Command::Version, "--version", "show version information" )
        , std::make_tuple( SteelContext::Command::MsiKeyboard, "msi-keyboard", "use msi keyboard hid device" )
        , std::make_tuple( SteelContext::Command::Rival, "rival-100", "use rival-100 mouse hid device" ) };


        SteelContext::SteelContext()
            : IContext{ "" }
            , _command{ Command::Invalid }
        {
        }


        int SteelContext::create( int argc, char* argv[] )
        {
            _command = Command::Invalid;

            if ( argc < 2 )
                return _error( -199, "no command specified, use --help for syntax help" );

            if ( argc > 1 )
            {
                auto pos = std::find_if( _commands.begin(), _commands.end(), [this,argv]( const std::tuple<SteelContext::Command,std::string,std::string>& object )
                {
                    if ( std::get<1>( object ) == argv[1] )
                        return true;
                    return false;
                } );

                if ( pos != _commands.end() )
                    _command = std::get<0>( *pos );
                else
                {
                    std::cout << syntax( 0 ) << std::endl;
                    return _error( -199, "undefined command \'%s\'", argv[1] );
                }
            }

            if (   ( argc > 2)
                && (   ( _command == Command::Help )
                    || ( _command == Command::Query )
                    || ( _command == Command::Version ) ) )
                return _error( -198, "no additional options allowed for command \'%s\'", argv[1] );

            return 0;
        }


        std::string SteelContext::syntax( int indent ) const
        {
            const int align = 30;
            std::string fill( indent, ' ' );
            std::string syntax( "syntax: " );
            std::string name( " <name>" );
            std::ostringstream sstr;

            sstr << std::endl
                 << fill << syntax << "steel [command]" << std::endl
                 << std::endl
                 << fill << std::string( syntax.size(), ' ' ) << "command:" << std::endl;

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

            sstr << std::endl
                 << fill << std::string( syntax.size(), ' ' ) << "remarks:" << std::endl
                 << fill << std::string( syntax.size(), ' ' ) << "- use \'steel [device] --help\' for more detailed device information" << std::endl
                 << fill << std::string( syntax.size(), ' ' ) << "- use \'steel\' to execute default action on all supported hid devices" << std::endl;

            return sstr.str();
        }


        SteelContext::Command SteelContext::command() const
        {
            return _command;
        }


        int SteelContext::_error( int result, const char* fmt, ... )
        {
            const int error = -32000;
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
