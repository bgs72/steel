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


#include <memory>
#include "config/Rival100Config.h"
#include "config/SteelConfig.h"
#include "config/Rival100Profile.h"
#include "context/Rival100Context.h"
#include "device/MsiKeyboard.h"
#include "actions/IActions.h"


namespace steel
{
    namespace actions
    {
        class Rival100Actions : public IActions
        {
            public:
                Rival100Actions() = delete;
                Rival100Actions( const steel::config::SteelConfig& config, const std::vector<steel::device::HidDeviceInfo>& devices );


                virtual int exec( int argc, char* argv[] );


            private:
                int _execActive( const steel::context::Rival100Context& context );
                int _execProfile( const steel::context::Rival100Context& context );
                int _execProfile( const steel::config::Rival100Profile& profile );
                int _error( int result, const char* fmt, ... );


            private:
                const steel::config::Rival100Config& _config;
                std::unique_ptr<steel::device::Rival100> _device;
        };
    }
}
