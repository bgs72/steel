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


#include <vector>
#include "device/MsiKeyboard.h"
#include "parser/IDeviceParser.h"


namespace steel
{
    namespace parser
    {
        class MsiKeyboardParser : public IDeviceParser
        {
            public:
                MsiKeyboardParser( std::ifstream& file, int& lineNumber, const std::string& fpath );
                virtual ~MsiKeyboardParser();


                int parse( std::shared_ptr<steel::config::IDeviceConfig> config );


            private:
                static std::vector<const char*> _keywords;
                static std::vector<std::tuple<steel::device::MsiKeyboard::Mode,std::string>> _modes;
                static std::vector<std::tuple<steel::device::MsiKeyboard::Intensity,std::string>> _intenseties;
                static std::vector<std::tuple<steel::device::MsiKeyboard::Color,std::string>> _colors;
        };
    }
}
