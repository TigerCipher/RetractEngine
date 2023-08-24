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
// File Name: Move
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Move.h"


#include "Retract/Components/Entity.h"

using namespace retract;

void Move::Update(f32 delta)
{
    if(!math::NearZero(m_angular_speed))
    {
        f32 rot = mOwner->Rotation();
        rot += m_angular_speed * delta;
        mOwner->SetRotation(rot);
    }

    if(!math::NearZero(m_forward_speed))
    {
        vec2 pos = mOwner->Position();
        pos += mOwner->Forward() * m_forward_speed * delta;
        if (pos.x < -500.f)
            pos.x = 498.f;
        else if (pos.x > 500.f)
            pos.x = -498.f;

        if (pos.y < -400.f)
            pos.y = 398.f;
        else if (pos.y > 400.f)
            pos.y = -398.f;

        mOwner->SetPosition(pos);
        
    }
}
