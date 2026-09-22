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
#include <locale>
#include "utils/Utils.h"


namespace steel
{
    namespace utils
    {
        std::string& trim( std::string& str )
        {
           return ltrim( rtrim( str ) );
        }


        std::string trim_copy( const std::string& str )
        {
            auto temp = str;
            return ltrim( rtrim( temp ) );
        }


        std::string& ltrim( std::string& str )
        {
            auto it =  std::find_if( str.begin(), str.end(), []( char ch )
            {
                return !std::isspace<char>( ch, std::locale::classic() );
            } );

            str.erase( str.begin(), it);
            return str;
        }


        std::string& rtrim( std::string& str )
        {
            auto it =  std::find_if( str.rbegin(), str.rend(), []( char ch )
            {
                return !std::isspace<char>( ch, std::locale::classic() );
            } );

            str.erase( it.base(), str.end() );
            return str;
        }
    }
}
