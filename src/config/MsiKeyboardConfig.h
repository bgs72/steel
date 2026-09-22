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
#include "config/IDeviceConfig.h"
#include "config/MsiKeyboardProfile.h"


namespace steel
{
    namespace parser
    {
        class MsiKeyboardParser;
    }


    namespace config
    {
        /**
         *  @brief MSI keyboard configuration.
         *
         *  File layout:
         *
         *  [msi-keyboard]
         *  profile = name,mode{,intensity}{,color1:color2:color3}{,speed}
         *  active = profile-name
         *
         *  Valid values:
         *  name            := any text without delimeters (',' and ':')
         *  mode            := disable, normal, game, breathe, wave, bicolor
         *  intensity       := low, medium, high, max
         *  color{1,2,3}    := black, red, orange, yellow, green, sky, blue, purple, white

         *  Example:
         *  profile = off, disable
         *  profile = default, normal, low, red : purple : sky
         *  profile = game, game, low, red
         *  profile = breathe, breathe, low, red :  purple : sky, 100
         *  profile = wave, wave, low, red : purple : sky, 150
         *  profile = bicolor, bicolor, low, red :  blue, 200
         *  active = default
         *
         */
        class MsiKeyboardConfig : public IDeviceConfig
        {
            public:
                MsiKeyboardConfig() = delete;
                MsiKeyboardConfig( const std::string& deviceName );

                const MsiKeyboardProfile& active() const;
                const std::vector<MsiKeyboardProfile>& profiles() const;


            private:
                MsiKeyboardProfile _active;
                std::vector<MsiKeyboardProfile> _profiles;

                friend class steel::parser::MsiKeyboardParser;
        };
    }
}

