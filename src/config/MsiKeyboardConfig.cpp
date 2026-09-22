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


#include <fstream>
#include <iostream>
#include "config/MsiKeyboardConfig.h"


namespace steel
{
    namespace config
    {
        MsiKeyboardConfig::MsiKeyboardConfig( const std::string& deviceName )
            : IDeviceConfig{ IDeviceConfig::DeviceType::MsiKeyboard, deviceName }
        {
        }


        const MsiKeyboardProfile& MsiKeyboardConfig::active() const
        {
            return _active;
        }


        const std::vector<MsiKeyboardProfile>& MsiKeyboardConfig::profiles() const
        {
            return _profiles;
        }
    }
}
