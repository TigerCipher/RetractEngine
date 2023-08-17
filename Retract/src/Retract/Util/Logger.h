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
#pragma once

#include "Retract/Types.h"

#include <format>

namespace retract::logger
{

enum class LogLevel
{
    trace,
    debug,
    info,
    warn,
    error,
    fatal
};

namespace detail
{
void Output(LogLevel lvl, std::string_view msg);
}

}

#ifdef _DEBUG
    #define LOG_TRACE(msg, ...) retract::logger::detail::Output(retract::logger::LogLevel::trace, std::format(msg, ##__VA_ARGS__))
    #define LOG_DEBUG(msg, ...) retract::logger::detail::Output(retract::logger::LogLevel::debug, std::format(msg, ##__VA_ARGS__))
    #define LOG_INFO(msg, ...)  retract::logger::detail::Output(retract::logger::LogLevel::info, std::format(msg, ##__VA_ARGS__))
    #define LOG_WARN(msg, ...)  retract::logger::detail::Output(retract::logger::LogLevel::warn, std::format(msg, ##__VA_ARGS__))
    #define LOG_ERROR(msg, ...) retract::logger::detail::Output(retract::logger::LogLevel::error, std::format(msg, ##__VA_ARGS__))
    #define LOG_FATAL(msg, ...) retract::logger::detail::Output(retract::logger::LogLevel::fatal, std::format(msg, ##__VA_ARGS__))
#else
    #define LOG_TRACE(msg, ...)
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)
    #define LOG_WARN(msg, ...)
    #define LOG_ERROR(msg, ...)
    #define LOG_FATAL(msg, ...)
#endif
