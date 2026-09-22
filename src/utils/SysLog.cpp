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


#include <syslog.h>
#include "SysLog.h"


namespace steel
{
    namespace utils
    {
        SysLog& SysLog::instance()
        {
            static SysLog instance;
            return instance;
        }


        SysLog::~SysLog()
        {
            closelog();
        }


        void SysLog::debug( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            debug( fmt, vl );
            va_end( vl );
        }


        void SysLog::info( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            info( fmt, vl );
            va_end( vl );
        }


        void SysLog::notice( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            notice( fmt, vl );
            va_end( vl );
        }


        void SysLog::warning( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            warning( fmt, vl );
            va_end( vl );
        }


        void SysLog::error( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            error( fmt, vl );
            va_end( vl );
        }


        void SysLog::critical( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            critical( fmt, vl );
            va_end( vl );
        }


        void SysLog::alert( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            alert( fmt, vl );
            va_end( vl );
        }


        void SysLog::emergency( const char* fmt, ... )
        {
            va_list vl;
            va_start( vl, fmt );
            emergency( fmt, vl );
            va_end( vl );
        }


        void SysLog::debug( const char* fmt, va_list vl )
        {
            _syslog( LOG_DEBUG, fmt, vl );
        }


        void SysLog::info( const char* fmt, va_list vl )
        {
            _syslog( LOG_INFO, fmt, vl );
        }


        void SysLog::notice( const char* fmt, va_list vl )
        {
            _syslog( LOG_NOTICE, fmt, vl );
        }


        void SysLog::warning( const char* fmt, va_list vl )
        {
            _syslog( LOG_WARNING, fmt, vl );
        }


        void SysLog::error( const char* fmt, va_list vl )
        {
            _syslog( LOG_ERR, fmt, vl );
        }


        void SysLog::critical( const char* fmt, va_list vl )
        {
            _syslog( LOG_CRIT, fmt, vl );
        }


        void SysLog::alert( const char* fmt, va_list vl )
        {
            _syslog( LOG_ALERT, fmt, vl );
        }


        void SysLog::emergency( const char* fmt, va_list vl )
        {
            _syslog( LOG_EMERG, fmt, vl );
        }


        SysLog::SysLog()
        {
            openlog( "steel", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER );
        }


        void SysLog::_syslog( int priority, const char* fmt, va_list vl )
        {
            vsyslog( priority, fmt, vl );
        }


        SysLog& syslog()
        {
            return SysLog::instance();
        }
    }
}
