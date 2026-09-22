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
#include <vector>
#include <tuple>
#include "context/IContext.h"


namespace steel
{
    namespace context
    {
        class MsiKeyboardContext : public IContext
        {
            public:
                enum class Command { Invalid, Active, Profile, Help };


            public:
                MsiKeyboardContext() = delete;
                MsiKeyboardContext( const std::string& deviceName );


                int create( int argc, char* argv[] );
                std::string syntax( int indent = 0 ) const;
                Command command() const;
                const std::string& profile() const;


            private:
                int _error( int result, const char* fmt, ... );


            private:
                Command _command;
                std::string _profile;

                static std::string _deviceName;
                static std::vector<std::tuple<Command,std::string,std::string>> _commands;
        };
    }
}
