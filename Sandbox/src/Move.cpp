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
        f32 rot = m_owner->Rotation();
        rot += m_angular_speed * delta;
        m_owner->SetRotation(rot);
    }

    if(!math::NearZero(m_forward_speed))
    {
        vec2 pos = m_owner->Position();
        pos += m_owner->Forward() * m_forward_speed * delta;
        if (pos.x < 0.0f)
            pos.x = 998.0f;
        else if (pos.x > 1000.0f)
            pos.x = 2.0f;

        if (pos.y < 0.0f)
            pos.y = 798.0f;
        else if (pos.y > 800.0f)
            pos.y = 2.0f;

        m_owner->SetPosition(pos);
        
    }
}
