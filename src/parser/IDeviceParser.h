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


#include <fstream>
#include <memory>
#include <string>
#include "config/IDeviceConfig.h"


namespace steel
{
    namespace parser
    {
        class IDeviceParser
        {
            public:
                IDeviceParser() = delete;
                IDeviceParser( std::ifstream& file, int& lineNumber, const std::string& fpath );
                IDeviceParser( const IDeviceParser& other ) = delete;
                IDeviceParser( IDeviceParser&& other ) = delete;
                IDeviceParser& operator = ( const IDeviceParser& other ) = delete;
                IDeviceParser& operator = ( IDeviceParser&& other ) = delete;
                virtual ~ IDeviceParser();


                virtual int parse( std::shared_ptr<steel::config::IDeviceConfig> config ) = 0;


            protected:
                virtual bool _getline( std::string& line );
                virtual int _error( int result, const char* fmt, ... );


            private:
                std::ifstream& _stream;
                int& _lineNumber;
                std::string _fpath;
        };
    }
}
