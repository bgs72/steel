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
#include <map>
#include <hidapi/hidapi.h>


namespace steel
{
    namespace device
    {
        class HidDeviceInfo
        {
            public:
                enum class Type { Unsupported, MsiKeyboard, Rival100 };


            public:                
                HidDeviceInfo() = delete;
                HidDeviceInfo( hid_device_info* deviceInfo );
                virtual ~HidDeviceInfo() = default;


                const std::string& path() const;
                unsigned short vendorId() const;
                unsigned short productId() const;
                const std::wstring& serial() const;
                unsigned short releaseNumber() const;
                const std::wstring& product() const;
                const std::wstring& manufacturer() const;
                unsigned short usagePage() const;
                unsigned short usage() const;
                int interface() const;
                Type type() const;


                std::string toString( const int indent = 0 ) const;


            private:
                std::string _w2a( const std::wstring& str ) const;


            private:
                std::string _path;
                unsigned short _vendorId;
                unsigned short _productId;
                std::wstring _serial;
                unsigned short _releaseNumber;
                std::wstring _product;
                std::wstring _manufacturer;
                unsigned short _usagePage;
                unsigned short _usage;
                int _interface;
                Type _type;
                static std::map<HidDeviceInfo::Type,std::string> _names;
        };
    }
}
