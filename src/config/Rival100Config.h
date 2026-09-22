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
#include "config/Rival100Profile.h"


namespace steel
{
    namespace parser
    {
        class Rival100Parser;
    }


    namespace config
    {
        /**
         *  @brief Rival configuration.
         *
         *  File layout:
         *
         *  [rival]
         *  profile = name,color,breathe,cpi1,cpi2,pollingrate
         *  active = profile-name
         *
         *  Valid values:
         *  name            := any text without delimeters (',' and ':')
         *  color           := black, red, orange, yellow, green, sky, blue, purple, white, #RRGGBB
         *  breathe         := off, slow, medium, fast
         *  cpi[1/2]        := 500 to 2250, in increments of 250
         *  pollingrate     := low, medium, high, max
         *
         *  Example:
         *  profile = off, black, off, 750, 1750, low
         *  profile = default, sky, slow, 750, 1750, high
         *  profile = game, red, high, 1250, 2250, max
         *  active = default
         *
         */
        class Rival100Config : public IDeviceConfig
        {
            public:
                Rival100Config() = delete;
                Rival100Config( const std::string& deviceName );


                const Rival100Profile& active() const;
                const std::vector<Rival100Profile>& profiles() const;


            private:
                Rival100Profile _active;
                std::vector<Rival100Profile> _profiles;

                friend class steel::parser::Rival100Parser;
        };
    }
}

