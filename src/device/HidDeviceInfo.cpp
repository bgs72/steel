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


#include <vector>
#include <sstream>
#include <hidapi/hidapi.h>
#include "device/IHidDevice.h"
#include "device/HidDeviceInfo.h"


namespace steel
{
    namespace device
    {
        std::map<HidDeviceInfo::Type,std::string> HidDeviceInfo::_names =
        { std::make_pair( HidDeviceInfo::Type::Unsupported, "unsupported" )
        , std::make_pair( HidDeviceInfo::Type::MsiKeyboard, "msi-keyboard" )
        , std::make_pair( HidDeviceInfo::Type::Rival100, "rival-100" ) };


        HidDeviceInfo::HidDeviceInfo( hid_device_info* deviceInfo )
            : _path{ deviceInfo->path }
            , _vendorId{ deviceInfo->vendor_id }
            , _productId{ deviceInfo->product_id }
            , _serial{ deviceInfo->serial_number ? deviceInfo->serial_number : std::wstring() }
            , _product{ deviceInfo->product_string ? deviceInfo->product_string : std::wstring() }
            , _manufacturer{ deviceInfo->manufacturer_string ? deviceInfo->manufacturer_string : std::wstring() }
            , _usagePage{ deviceInfo->usage_page }
            , _usage{ deviceInfo->usage }
            , _interface{ deviceInfo->interface_number }
            , _type{ Type::Unsupported }
        {
            if (   ( _vendorId == 0x1770 )
                && ( _productId == 0xff00 )
                && ( _interface == 0 ) )
            {
                _type = Type::MsiKeyboard;
            }
            else if (   ( _vendorId == 0x1038 )
                     && ( _productId == 0x1702 )
                     && ( _interface == 0 ) )
            {
                _type = Type::Rival100;
            }
        }


        const std::string& HidDeviceInfo::path() const
        {
            return _path;
        }


        unsigned short HidDeviceInfo::vendorId() const
        {
            return _vendorId;
        }


        unsigned short HidDeviceInfo::productId() const
        {
            return _productId;
        }


        const std::wstring& HidDeviceInfo::serial() const
        {
            return _serial;
        }


        unsigned short HidDeviceInfo::releaseNumber() const
        {
            return _releaseNumber;
        }


        const std::wstring& HidDeviceInfo::product() const
        {
            return _product;
        }


        const std::wstring& HidDeviceInfo::manufacturer() const
        {
            return _manufacturer;
        }


        unsigned short HidDeviceInfo::usagePage() const
        {
            return _usagePage;
        }


        unsigned short HidDeviceInfo::usage() const
        {
            return _usage;
        }


        int HidDeviceInfo::interface() const
        {
            return _interface;
        }


        HidDeviceInfo::Type HidDeviceInfo::type() const
        {
            return _type;
        }


        std::string HidDeviceInfo::toString( const int indent ) const
        {
            std::string fill( indent, ' ' );
            std::ostringstream stream;
            std::string type = _names[_type];

            stream << fill << "+ hid device info" << std::endl
                   << fill << "  . path           : " << _path << std::endl
                   << fill << "  . vendor id      : 0x" << std::hex << _vendorId << std::endl
                   << fill << "  . product id     : 0x" << _productId << std::dec << std::endl
                   << fill << "  . serial         : " << IHidDevice::w2a( _serial ) << std::endl
                   << fill << "  . release number : " << _releaseNumber << std::endl
                   << fill << "  . product        : " << IHidDevice::w2a( _product ) << std::endl
                   << fill << "  . manufacturer   : " << IHidDevice::w2a( _manufacturer ) << std::endl
                   << fill << "  . usage page     : " << _usagePage << std::endl
                   << fill << "  . usage          : " << _usage << std::endl
                   << fill << "  . interface      : " << _interface << std::endl
                   << fill << "  . type           : " << type << std::endl;

            return stream.str();
        }
    }
}
