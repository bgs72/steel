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
#include "device/Rival100.h"


namespace steel
{
    namespace parser
    {
        class Rival100Parser;
    }


    namespace config
    {
        class Rival100Profile
        {
            public:
                Rival100Profile();


                const std::string& name() const;
                steel::device::Rival100::RGB color() const;
                steel::device::Rival100::Breathe breathe() const;
                unsigned int cpi1() const;
                unsigned int cpi2() const;
                steel::device::Rival100::PollingRate pollingRate() const;


            private:
                std::string _name;
                steel::device::Rival100::RGB _color;
                steel::device::Rival100::Breathe _breathe;
                unsigned int _cpi1;
                unsigned int _cpi2;
                steel::device::Rival100::PollingRate _pollingRate;

                friend class steel::parser::Rival100Parser;
        };
    }
}
