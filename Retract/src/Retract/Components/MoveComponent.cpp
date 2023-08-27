//  ------------------------------------------------------------------------------
//
//  RetractEngine
//     Copyright 2023 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  File Name: MoveComponent.h
//  Date File Created: 08/25/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------


#include "MoveComponent.h"


#include "Entity.h"


namespace retract
{

void MoveComponent::Update(f32 delta)
{
    if (!math::NearZero(mAngularSpeed))
    {
        quaternion rot   = mOwner->Rotation();
        const f32  angle = mAngularSpeed * delta;

        // Incremental rotation about up axis
        const quaternion inc{ math::unitz_vec3, angle };

        // concat old and new rotation
        rot = math::Concatinate(rot, inc);
        mOwner->SetRotation(rot);
    }

    if (!math::NearZero(mForwardSpeed))
    {
        vec3 pos = mOwner->Position();
        pos += mOwner->Forward() * mForwardSpeed * delta;
        mOwner->SetPosition(pos);
    }
}

} // namespace retract