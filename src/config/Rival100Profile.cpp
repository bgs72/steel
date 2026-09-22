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


#include "config/Rival100Profile.h"


using namespace steel::device;


namespace steel
{
    namespace config
    {
        Rival100Profile::Rival100Profile()
            : _name{ "default" }
            , _color( Rival100::RGB::fromColor( Rival100::RGB::Color::Orange ) )
            , _breathe{ Rival100::Breathe::Slow }
            , _cpi1{ 500 }
            , _cpi2{ 1500 }
            , _pollingRate{ Rival100::PollingRate::High }
        {
        }


        const std::string& Rival100Profile::name() const
        {
            return _name;
        }


        Rival100::RGB Rival100Profile::color() const
        {
            return _color;
        }


        Rival100::Breathe Rival100Profile::breathe() const
        {
            return _breathe;
        }


        unsigned int Rival100Profile::cpi1() const
        {
            return _cpi1;
        }


        unsigned int Rival100Profile::cpi2() const
        {
            return _cpi2;
        }


        Rival100::PollingRate Rival100Profile::pollingRate() const
        {
            return _pollingRate;
        }
    }
}
