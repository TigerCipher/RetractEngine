// ------------------------------------------------------------------------------
//
// RetractEngine
//    Copyright 2023 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Logger
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Logger.h"
//#include <cstdio>
#include <ctime>
#include <iomanip>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace retract::logger::detail
{

namespace
{
std::string CurrentTimeStamp()
{
    const auto         t  = std::time(nullptr);
    const auto         tm = *std::localtime(&t); // NOTE: Not thread safe
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    return oss.str();
}
} // anonymous namespace

void Output(LogLevel lvl, std::string_view msg)
{
    std::string str;
    std::string time_stamp = CurrentTimeStamp();
    switch (lvl)
    {
    case LogLevel::trace: str = std::format("[{}][  TRACE  ]: {}\n", time_stamp, msg); break;
    case LogLevel::debug: str = std::format("[{}][  DEBUG  ]: {}\n", time_stamp, msg); break;
    case LogLevel::info: str = std::format("[{}][  INFO   ]: {}\n", time_stamp, msg); break;
    case LogLevel::warn: str = std::format("[{}][ WARNING ]: {}\n", time_stamp, msg); break;
    case LogLevel::error: str = std::format("[{}][  ERROR  ]: {}\n", time_stamp, msg); break;
    case LogLevel::fatal: str = std::format("[{}][  FATAL  ]: {}\n", time_stamp, msg); break;
    }

    OutputDebugStringA(str.c_str());

    //printf("%s", str.c_str());
}
} // namespace retract::logger::detail