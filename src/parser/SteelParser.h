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


#include <string>
#include <tuple>
#include <vector>
#include <config/IDeviceConfig.h>
#include "config/SteelConfig.h"


namespace steel
{
    namespace parser
    {
        class SteelParser
        {
            public:
                SteelParser() = delete;
                SteelParser( const std::string& fpath );
                SteelParser( const SteelParser& other ) = default;
                SteelParser( SteelParser&& other ) = default;
                SteelParser& operator = ( const SteelParser& other ) = default;
                SteelParser& operator = ( SteelParser&& other ) = default;
                ~SteelParser() = default;


                int parse( steel::config::SteelConfig& config );


            private:
                int _error( int result, const char* fmt, ... );

            private:
                std::string _fpath;
                std::string _line;
                int _lineNumber;

                static std::vector<std::tuple<steel::config::IDeviceConfig::DeviceType,std::string>> _deviceTypes;
        };
    }
}
