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
// File Name: Asteroid
// Date File Created: 08/19/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once


#include "Circle.h"
#include "Move.h"
#include "Retract/Common.h"
#include "Retract/Components/Entity.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"

class Asteroid : public retract::Entity
{
public:
    Asteroid(retract::Game* game);
    ~Asteroid() override;
    void UpdateEntity(f32 delta) override {}

    Circle* GetCircle() const { return m_circle; }

private:
    retract::Sprite* m_sprite{ nullptr };
    Circle*          m_circle{ nullptr };
    Move*            mc{ nullptr };
};