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


#include <stdarg.h>


namespace steel
{
    namespace utils
    {
        class SysLog
        {
            public:
                static SysLog& instance();

                ~SysLog();
                void debug( const char* fmt, ... );
                void info( const char* fmt, ... );
                void notice( const char* fmt, ... );
                void warning( const char* fmt, ... );
                void error( const char* fmt, ... );
                void critical( const char* fmt, ... );
                void alert( const char* fmt, ... );
                void emergency( const char* fmt, ... );


                void debug( const char*, va_list vl );
                void info( const char*, va_list vl );
                void notice( const char*, va_list vl );
                void warning( const char*, va_list vl );
                void error( const char*, va_list vl );
                void critical( const char*, va_list vl );
                void alert( const char*, va_list vl );
                void emergency( const char*, va_list vl );


                // todo: setlogmask


            private:
                void _syslog( int priority, const char* fmt, va_list vl );

                SysLog();
                SysLog( const SysLog& other ) = delete;
                SysLog( SysLog&& other ) = delete;
                const SysLog& operator = ( const SysLog& other ) = delete;
                SysLog& operator = ( SysLog&& other ) = delete;
        };


        SysLog& syslog();
    }
}
