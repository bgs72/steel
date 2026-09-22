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
#include <hidapi/hidapi.h>
#include "device/HidDeviceInfo.h"


namespace steel
{
    namespace device
    {
        class IHidDevice
        {
            public:
                enum class Type { MsiKeyboard, Rival100 };


            public:
                IHidDevice() = delete;
                IHidDevice( const HidDeviceInfo& hidDeviceInfo );
                IHidDevice( const IHidDevice& other ) = delete;
                IHidDevice( IHidDevice&& other ) = delete;
                IHidDevice& operator = ( const IHidDevice& other ) = delete;
                IHidDevice& operator = ( IHidDevice&& other ) = delete;
                virtual ~IHidDevice();


                static std::vector<HidDeviceInfo> enumerate();
                static std::string w2a( const std::wstring& wstr );


            protected:
                hid_device* _device;
        };
    }
}
