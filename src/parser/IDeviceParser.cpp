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
#include "utils/SysLog.h"
#include "utils/Utils.h"
#include "parser/IDeviceParser.h"


using namespace steel::utils;


namespace steel
{
    namespace parser
    {
        IDeviceParser::IDeviceParser( std::ifstream& stream, int& lineNumber, const std::string& fpath )
            : _stream( stream )
            , _lineNumber{ lineNumber }
            , _fpath( fpath )
        {
        }


        IDeviceParser::~IDeviceParser()
        {
        }


        bool IDeviceParser::_getline( std::string& line )
        {
            while ( std::getline( _stream, line ) )
            {
                ++_lineNumber;
                trim( line );

                if ( line.empty() )
                    return false;       // empty line marks end of device section!

                if ( line.at( 0 ) == '#' )
                    continue;

                return true;
            }

            return false;
        }


        int IDeviceParser::_error( int result, const char* fmt, ... )
        {
            const int error = -50000;
            std::vector<char> buffer( 16384 );
            va_list vl;

            va_start( vl, fmt );
            std::vsprintf( buffer.data(), fmt, vl );
            syslog().error( "error (%d): at line %d in file %s: %s", result += error, _lineNumber, _fpath.c_str(), buffer.data() );
            std::fprintf( stderr, "\nerror (%d): at line %d in file %s: %s\n\n", result, _lineNumber, _fpath.c_str(), buffer.data() );
            return result;
        }
    }
}
