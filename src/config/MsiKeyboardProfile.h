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
#include "device/MsiKeyboard.h"


namespace steel
{
    namespace parser
    {
        class MsiKeyboardParser;
    }


    namespace config
    {
        class MsiKeyboardProfile
        {
            public:
                MsiKeyboardProfile();


                const std::string& name() const;
                steel::device::MsiKeyboard::Mode mode() const;
                steel::device::MsiKeyboard::Intensity intensity() const;
                steel::device::MsiKeyboard::Color color1() const;
                steel::device::MsiKeyboard::Color color2() const;
                steel::device::MsiKeyboard::Color color3() const;
                int speed() const;


            private:
                std::string _name;
                steel::device::MsiKeyboard::Mode _mode;
                steel::device::MsiKeyboard::Intensity _intensity;
                steel::device::MsiKeyboard::Color _color1;
                steel::device::MsiKeyboard::Color _color2;
                steel::device::MsiKeyboard::Color _color3;
                int _speed;

                friend class steel::parser::MsiKeyboardParser;
        };
    }
}
