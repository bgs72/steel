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


#include "config/MsiKeyboardProfile.h"


using namespace steel::device;


namespace steel
{
    namespace config
    {
        MsiKeyboardProfile::MsiKeyboardProfile()
            : _name{ "default" }
            , _mode{ MsiKeyboard::Mode::Normal }
            , _intensity{ MsiKeyboard::Intensity::High }
            , _color1{ MsiKeyboard::Color::White }
            , _color2{ MsiKeyboard::Color::White }
            , _color3{ MsiKeyboard::Color::White }
            , _speed{ -1 }
        {
        }


        const std::string& MsiKeyboardProfile::name() const
        {
            return _name;
        }


        MsiKeyboard::Mode MsiKeyboardProfile::mode() const
        {
            return _mode;
        }


        MsiKeyboard::Intensity MsiKeyboardProfile::intensity() const
        {
            return _intensity;
        }


        MsiKeyboard::Color MsiKeyboardProfile::color1() const
        {
            return _color1;
        }


        MsiKeyboard::Color MsiKeyboardProfile::color2() const
        {
            return _color2;
        }


        MsiKeyboard::Color MsiKeyboardProfile::color3() const
        {
            return _color3;
        }


        int MsiKeyboardProfile::speed() const
        {
            return _speed;
        }
    }
}
