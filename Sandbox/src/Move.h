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

#pragma once
#include "Retract/Components/Component.h"


class Move : public retract::Component
{
public:
    Move(retract::Entity* owner, i32 update_order = 10) : Component{owner, update_order} {}
    void Update(f32 delta) override;

    constexpr f32 AngularSpeed() const { return m_angular_speed; }
    constexpr f32 ForwardSpeed() const { return m_forward_speed; }

    void SetAngularSpeed(f32 speed) { m_angular_speed = speed; }
    void SetForwardSpeed(f32 speed) { m_forward_speed = speed; }

private:
    f32 m_angular_speed{};
    f32 m_forward_speed{};

};
