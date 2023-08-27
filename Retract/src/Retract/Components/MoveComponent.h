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

#pragma once

#include "Component.h"

namespace retract
{
class MoveComponent : public Component
{
public:
    MoveComponent(Entity* owner, i32 update_order = 10) : Component(owner, update_order) {}
    void Update(f32 delta) override;

    void SetAngularSpeed(f32 speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(f32 speed) { mForwardSpeed = speed; }

    constexpr f32 AngularSpeed() const { return mAngularSpeed; }
    constexpr f32 ForwardSpeed() const { return mForwardSpeed; }

private:
    f32 mAngularSpeed{};
    f32 mForwardSpeed{};
};

} // namespace retract
