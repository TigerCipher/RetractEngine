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
// File Name: Util
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Util.h"


#include <cassert>

namespace retract::random
{
namespace
{
std::mt19937 generator;  // NOLINT(cert-msc51-cpp)
bool initialized{false};
} // anonymous namespace

void Init()
{
    std::random_device rd;
    Seed(rd());
    initialized = true;
}

void Seed(u32 seed)
{
    generator.seed(seed);
}

f32 Float(f32 min, f32 max)
{
    assert(initialized);
    std::uniform_real_distribution<f32> dist{ min, max };
    return dist(generator);
}

i32 Int(i32 min, i32 max)
{
    assert(initialized);
    std::uniform_int_distribution<i32> dist{ min, max };
    return dist(generator);
}

vec2 Vector(const vec2& min, const vec2& max)
{
    assert(initialized);
    const vec2 r{ Float(), Float() };
    return min + (max - min) * r;
}

vec3 Vector(const vec3& min, const vec3& max)
{
    assert(initialized);
    const vec3 r{ Float(), Float(), Float() };
    return min + (max - min) * r;
}
} // namespace retract::random