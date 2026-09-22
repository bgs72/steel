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


#include "device/IHidDevice.h"


namespace steel
{
    namespace device
    {
        class Rival100 : public IHidDevice
        {
            public:
                enum class Breathe { Off = 1, Slow, Medium, Fast };
                enum class PollingRate { Max = 1, High, Medium, Low };


                struct RGB
                {
                    unsigned char r;
                    unsigned char g;
                    unsigned char b;

                    enum Color
                    {
                        Black = 0x000000
                    ,   Red = 0xFF0000
                    ,   Orange = 0xFF4500
                    ,   Yellow = 0xFFFF00
                    ,   Green = 0x00FF00
                    ,   Sky = 0x00FFFF
                    ,   Blue =  0x0000FF
                    ,   Purple = 0xFF00FF
                    ,   White = 0xFFFFFF
                    };

                    static RGB fromColor( RGB::Color value )
                    {
                        RGB rgb;
                        rgb.r = ( value >> 16 ) & 0xFF;
                        rgb.g = ( value >> 8 ) & 0xFF;
                        rgb.b = value & 0xFF;
                        return rgb;
                    }

                    static int fromString( const std::string& value, RGB& color )
                    {
                        if (   ( value.size() >= 7 )
                            && ( value.at( 0 ) == '#' ) )
                        {
                            color.r = std::stoi( value.substr( 1, 3 ), 0, 16 );
                            color.g = std::stoi( value.substr( 3, 5 ), 0, 16 );
                            color.b = std::stoi( value.substr( 5, 7 ), 0, 16 );
                            return 0;
                        }

                        return -1;
                    }
                };


            public:
                Rival100() = delete;
                Rival100( const HidDeviceInfo& hidDeviceInfo );

                int setSensitivity( const unsigned int cpi1, const unsigned int cpi2 );
                int setPollingRate( const PollingRate value );
                int setColor( const RGB& value );
                int setBreathe( const Breathe value );
                int commit();


            private:
                int _setCpi( const unsigned char index, const unsigned int value );
                int _send( const std::vector<unsigned char>& raw );
                int _error( int result, const char* fmt, ... );
        };
    }
}
