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
// File Name: Circle
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Circle.h"


#include "Retract/Components/Entity.h"

using namespace retract;

f32 Circle::Radius() const
{
    return m_owner->Scale() * m_radius;
}

vec2 Circle::Center() const
{
    return m_owner->Position();
}

bool Intersect(const Circle& a, const Circle& b)
{
    vec2 diff    = a.Center() - b.Center();
    f32  distsq  = diff.LengthSq();
    f32  radiisq = a.Radius() + b.Radius();
    radiisq *= radiisq;

    return distsq <= radiisq;
}
