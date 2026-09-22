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


#pragma once


#include <algorithm>
#include <vector>
#include <tuple>


namespace steel
{
    namespace utils
    {
        template <typename T, typename U> bool lookup( const std::vector<std::tuple<T, U>>& table, const U& key, T& value )
        {
            auto pos = std::find_if( table.begin(), table.end(), [key]( const std::tuple<T, U>& object )->bool
            {
                if ( key == std::get<1>( object ) )
                    return true;
                return false;
            } );

            if ( pos == table.end() )
                return false;

            value = std::get<0>( *pos );
            return true;
        }
    }
}
