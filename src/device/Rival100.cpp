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


#include <cmath>
#include <unistd.h>
#include "utils/SysLog.h"
#include "device/Rival100.h"

#include <iostream>

using namespace steel::utils;


namespace steel
{
    namespace device
    {
        Rival100::Rival100( const HidDeviceInfo& hidDeviceInfo )
            : IHidDevice{ hidDeviceInfo }
        {
        }


        int Rival100::setSensitivity( const unsigned int cpi1, const unsigned int cpi2 )
        {
            int result;

            if (   ( ( result =_setCpi( 1, cpi1 ) ) != 0 )
                || ( ( result = _setCpi( 2, cpi2 ) ) != 0 ) )
                return result;

            return 0;
        }


        int Rival100::setPollingRate( const PollingRate rate )
        {
            std::vector<unsigned char> raw( 32, 0x00 );

            raw[0] = 0x04;
            raw[2] = static_cast<unsigned char>( rate );

            return _send( raw );
        }


        int Rival100::setColor( const RGB& value )
        {
            std::vector<unsigned char> raw( 32, 0x00 );

            raw[0] = 0x05;
            raw[2] = value.r;
            raw[3] = value.g;
            raw[4] = value.b;

            return _send( raw );
        }


        int Rival100::setBreathe( const Breathe value )
        {
            std::vector<unsigned char> raw( 32, 0x00 );

            raw[0] = 0x07;
            raw[2] = static_cast<unsigned char>( value );

            return _send( raw );
        }


        int Rival100::commit()
        {
            std::vector<unsigned char> raw( 32, 0x09 );
            return _send( raw );
        }


        int Rival100::_setCpi( const unsigned char index, const unsigned int value )
        {
            if (   ( value < 500 )
                || ( value > 2250 )
                || ( value % 250 ) )
                return _error( -100, "invalid value for cpi-%d (%d)", index, value );

            std::vector<unsigned char> raw( 32, 0x00 );

            raw[0] = 0x03;
            raw[1] = index;
            raw[2] = 8 - ( ( value - 500 ) / 250 );

            return _send( raw );
        }


        int Rival100::_send( const std::vector<unsigned char>& raw )
        {
            if ( _device == 0 )
            {
                if ( geteuid() != 0 )
                    return _error( -4, "not initialized (needs root permission)" );
                return _error( -3, "not initialized" );
            }

            int result = hid_send_feature_report( _device, raw.data(), raw.size() );

            if ( result < 0 )
                return _error( -1, "%s", w2a( hid_error( _device ) ).c_str() );
            else if ( result != static_cast<int>( raw.size() ) )
                return _error( -2, "expected to write %d bytes, wrote %d bytes", raw.size(), result );

            return 0;
        }


        int Rival100::_error( int result, const char* fmt, ... )
        {
            const int error = -41000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): rival-100 error: %s", result += error, buffer.data() );
            std::fprintf( stderr, "\nerror (%d): rival-100 error: %s\n\n", result, buffer.data() );
            return result;
        }
    }
}

