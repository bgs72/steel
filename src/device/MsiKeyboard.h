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
        class MsiKeyboard : public IHidDevice
        {
            public:
                enum class Mode { Disable=0, Normal, Game, Breathe, Wave=5, BiColor };
                enum class Area { Left=1, Middle, Right };
                enum class Color { Black=0, Red, Orange, Yellow, Green, Sky, Blue, Purple, White };
                enum class Intensity { Low=0, Medium, High, Max };
                enum class View { Single=0, Primary, Secondary };


            public:
                MsiKeyboard() = delete;
                MsiKeyboard( const HidDeviceInfo& hidDeviceInfo );

                int disable();
                int normal( const Intensity intensity, const Color colors[3] );
                int gaming( const Intensity intensity, const Color color );
                int breathing( const Intensity intensity, const Color colors[3], const int speed = -1 );
                int wave( const Intensity intensity, const Color colors[3], const int speed = -1 );
                int bicolor( const Intensity intensity, const Color colors[2], const int speed = -1 );


            private:
                void _speed( const Color color1, const Color color2, const int speed, unsigned char ramps[3] );
                int _commit( const Mode mode );
                int _write( unsigned char mode, unsigned char area, unsigned char color, unsigned char intensity, unsigned char ramp );
                int _send( const std::vector<unsigned char>& raw );
                int _error( int result, const char* fmt, ... );

                static unsigned char _rgb[][3];
        };
    }
}
