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
// File Name: Ship
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Components/Entity.h"

class Ship : public retract::Entity
{
public:
    Ship(retract::core::Game* game);

    void UpdateEntity(f32 delta) override;

    void          ProcessKeyboard(const u8* state);
    constexpr f32 RightSpeed() const { return m_right_speed; }
    constexpr f32 DownSpeed() const { return m_down_speed; }

private:
    f32 m_right_speed{};
    f32 m_down_speed{};
};
