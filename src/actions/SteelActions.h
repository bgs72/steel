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


#include "config/SteelConfig.h"
#include "context/SteelContext.h"
#include "actions/IActions.h"


namespace steel
{
    namespace actions
    {
        class SteelActions : public IActions
        {
            public:
                SteelActions();

                int exec( int argc, char* argv[] );


            private:
                int _execHelp( const steel::context::SteelContext& context );
                int _execQuery();
                int _execVersion();
                int _execAllDevices( int argc, char* argv[], const steel::config::SteelConfig& config );
                int _execMsiKeyboard( int argc, char* argv[], const steel::config::SteelConfig& config );
                int _execRival100( int argc, char* argv[], const steel::config::SteelConfig& config );
                int _error( int result, const char* fmt, ... );


            private:
                static std::string _version;
        };
    }
}
