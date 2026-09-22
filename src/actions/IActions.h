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
#include "device/HidDeviceInfo.h"


namespace steel
{
    namespace actions
    {
        class IActions
        {
            public:
                IActions() = delete;
                IActions( const std::vector<steel::device::HidDeviceInfo>& devices );
                virtual ~IActions() = default;


                virtual int exec( int argc, char* argv[] ) = 0;


            protected:
                std::vector<steel::device::HidDeviceInfo> _devices;
        };
    }
}
