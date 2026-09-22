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
#include "device/MsiKeyboard.h"

#include <iostream>

using namespace steel::utils;


namespace steel
{
    namespace device
    {
        unsigned char MsiKeyboard::_rgb[][3]
            { {   0,   0,   0 }
            , { 255,   0,   0 }
            , { 187, 112,   0 }
            , { 238, 238,   0 }
            , { 176, 255,   0 }
            , {   0, 255, 255 }
            , {   0,   0, 255 }
            , {  48,   0, 255 }
            , { 176, 255, 176 } };


        MsiKeyboard::MsiKeyboard( const HidDeviceInfo& hidDeviceInfo )
            : IHidDevice{ hidDeviceInfo }
        {
        }


        int MsiKeyboard::disable()
        {
            return _commit( Mode::Disable );
        }


        int MsiKeyboard::normal( const Intensity intensity, const Color colors[3] )
        {
            for ( int result, i = 0; i < 3; ++i )
            {
                if ( ( result = _write( 0x42
                                      , i + 1
                                      , static_cast<unsigned char>( colors[i] )
                                      , static_cast<unsigned char>( intensity )
                                      , 0x00 ) ) != 0 )
                {
                    return result;
                }
            }

            return _commit( Mode::Normal );
        }


        int MsiKeyboard::gaming( const Intensity intensity, const Color color )
        {
            int result = _write( 0x42
                               , static_cast<unsigned char>( Area::Left )
                               , static_cast<unsigned char>( color )
                               , static_cast<unsigned char>( intensity )
                               , 0x00 );

            if ( result == 0 )
            {
                result = _commit( Mode::Game );
            }

            return ( result );
        }


        int MsiKeyboard::breathing( const Intensity intensity, const Color colors[3], const int speed )
        {
            unsigned char ramp[3];

            for ( int result, i = 0; i < 3; ++i )
            {
                _speed( colors[i], Color::Black, speed < 0 ? 100 : speed, ramp );

                if (   ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Left ) + ( i * 3 )
                                          , static_cast<unsigned char>( colors[i] )
                                          , static_cast<unsigned char>( intensity )
                                          , 0 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Middle ) + ( i * 3 )
                                          , 0x00
                                          , static_cast<unsigned char>( intensity )
                                          , 0x00 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Right ) + ( i * 3 )
                                          , ramp[0]
                                          , ramp[1]
                                          , ramp[2] ) ) != 0 ) )
                {
                    return result;
                }
            }

            return _commit( Mode::Breathe );
        }


        int MsiKeyboard::wave( const Intensity intensity, const Color colors[3], const int speed )
        {
            unsigned char ramp[3];

            for ( int result, i = 0; i < 3; ++i )
            {
                _speed( colors[i], Color::Black, speed < 0 ? 150 : speed, ramp );

                if (   ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Left ) + ( i * 3 )
                                          , static_cast<unsigned char>( colors[i] )
                                          , static_cast<unsigned char>( intensity )
                                          , 0 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Middle ) + ( i * 3 )
                                          , 0x00
                                          , static_cast<unsigned char>( intensity )
                                          , 0x00 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Right ) + ( i * 3 )
                                          , ramp[0]
                                          , ramp[1]
                                          , ramp[2] ) ) != 0 ) )
                {
                    return result;
                }
            }

            return _commit( Mode::Wave );
        }


        int MsiKeyboard::bicolor( const Intensity intensity, const Color colors[2], const int speed )
        {
            unsigned char ramp[3];

            _speed( colors[0], colors[1], speed < 0 ? 200 : speed, ramp );

            for ( int result, i = 0; i < 3; ++i )
            {
                if (   ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Left ) + ( i * 3 )
                                          , static_cast<unsigned char>( colors[0] )
                                          , ( colors[0] == Color::Black || colors[0] == Color::White ) ? 0 : static_cast<unsigned char>( intensity )
                                          , 0 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Middle ) + ( i * 3 )
                                            , static_cast<unsigned char>( colors[1] )
                                            , ( colors[1] == Color::Black || colors[1] == Color::White ) ? 0 : static_cast<unsigned char>( intensity )
                                            , 0 ) ) != 0 )
                    || ( ( result = _write( 0x43
                                          , static_cast<unsigned char>( Area::Right ) + ( i * 3 )
                                          , ramp[0]
                                          , ramp[1]
                                          , ramp[2] ) ) != 0 ) )
                {
                    return result;
                }
            }

            return _commit( Mode::BiColor );
        }


        void MsiKeyboard::_speed( const Color color1, const Color color2, const int speed, unsigned char ramps[3] )
        {
            unsigned char* rgb1 = _rgb[static_cast<int>( color1 )];
            unsigned char* rgb2 = _rgb[static_cast<int>( color2 )];

            for ( int i = 0; i < 3; ++i )
            {
                if ( rgb1[i] == rgb2[i] )
                {
                    ramps[i] = 0;
                }
                else
                {
                    ramps[i] = std::ceil( speed * 2.5 / std::abs( rgb1[i] - rgb2[i] ) );
                }
            }
        }


        int MsiKeyboard::_commit( const Mode mode )
        {
            std::vector<unsigned char> raw( 8, 0x00 );

            raw[0] = 0x01;
            raw[1] = 0x02;
            raw[2] = 0x41;
            raw[3] = static_cast<unsigned char>( mode );
            raw[7] = 0xEC;

            return _send( raw );
        }


        int MsiKeyboard::_write( unsigned char mode, unsigned char area, unsigned char color, unsigned char intensity, unsigned char ramp )
        {
            std::vector<unsigned char> raw( 8, 0x00 );

            raw[0] = 0x01;
            raw[1] = 0x02;
            raw[2] = mode;
            raw[3] = area;
            raw[4] = color;
            raw[5] = intensity;
            raw[6] = ramp;
            raw[7] = 0xEC;

            return _send( raw );
        }


        int MsiKeyboard::_send( const std::vector<unsigned char>& raw )
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


        int MsiKeyboard::_error( int result, const char* fmt, ... )
        {
            const int error = -40000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): msi-keyboard error: %s", result += error, buffer.data() );
            std::fprintf( stderr, "\nerror (%d): msi-keyboard error: %s\n\n", result, buffer.data() );
            return result;
        }
    }
}

