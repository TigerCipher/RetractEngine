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
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Types.h"
#include "Math.h"

#include <random>

#define USE_STL_VECTOR 1

#if USE_STL_VECTOR
    #include <vector>
namespace retract::utl
{
template<typename T>
using vector = std::vector<T>;
}
#endif

namespace retract::random
{

void Init();
void Seed(u32 seed);

f32 Float(f32 min = 0.f, f32 max = 1.f);
i32 Int(i32 min, i32 max);

vec2 Vector(const vec2& min, const vec2& max);
vec3 Vector(const vec3& min, const vec3& max);


} // namespace retract::random