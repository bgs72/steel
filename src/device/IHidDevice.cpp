//
//  Copyright 2015-2026
//  Author(s): Bart Gysens <2015-2026>
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


#include <chrono>
#include <thread>
#include "utils/SysLog.h"
#include "IHidDevice.h"


using namespace steel::utils;


namespace steel
{
    namespace device
    {
        IHidDevice::IHidDevice( const HidDeviceInfo& hidDeviceInfo )
            : _device{ hid_open( hidDeviceInfo.vendorId()
                               , hidDeviceInfo.productId()
                               , hidDeviceInfo.serial().empty() ? nullptr : hidDeviceInfo.serial().data() ) }
        {
            if ( _device == nullptr )
            {
                syslog().error( "unable to open hid device with vendor-id=0x%04X and product-id=%04X", hidDeviceInfo.vendorId(), hidDeviceInfo.productId() );
            }
        }


        IHidDevice::~IHidDevice()
        {
            hid_close( _device );
        }


        std::vector<HidDeviceInfo> IHidDevice::enumerate()
        {
            std::vector<HidDeviceInfo> devices;

            for ( int i = 1; i <= 10 && !devices.size(); ++i )
            {
                auto devs = hid_enumerate( 0, 0 );

                for( auto device = devs; device != nullptr; device = device->next )
                {
                    HidDeviceInfo hidDeviceInfo( device );
                    devices.push_back( HidDeviceInfo( device ) );
                }

                hid_free_enumeration( devs );
                std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
            }

            return devices;
        }


        std::string IHidDevice::w2a( const std::wstring& wstr )
        {
            std::vector<char> str( wstr.size() + 1, '\0' );
            std::wcstombs( str.data(), wstr.data(), str.size() );
            return str.data();
        }
    }
}

