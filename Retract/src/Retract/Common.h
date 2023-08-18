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
// File Name: Common
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include <cassert>
#include <unordered_map>

#include "Types.h"
#include "Util/Logger.h"
#include "Util/Util.h"


constexpr auto operator""_KB(const u64 x)
{
    return x * 1024u;
}

constexpr auto operator""_MB(const u64 x)
{
    return x * 1024u * 1024u;
}

constexpr auto operator""_GB(const u64 x)
{
    return x * 1024u * 1024u * 1024u;
}

// TEMP
struct Vector2
{
    f32 x;
    f32 y;
};

using vec2 = Vector2;