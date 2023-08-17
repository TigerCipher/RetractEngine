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
// File Name: Entity
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Common.h"

namespace retract
{

namespace core
{
class Game;
}

class Component;

class Entity
{
public:
    enum class State
    {
        active,
        suspended,
        dead
    };

    explicit Entity(core::Game* game);
    virtual ~Entity();

    void Update(f32 delta);
    void UpdateComponents(f32 delta);

    virtual void UpdateEntity(f32 delta);

    void AddComponent(Component* comp);
    void RemoveComponent(Component* comp);

    constexpr State CurrentState() const { return m_state; }

    core::Game* Game() const { return m_game; }

    constexpr vec2 Position() const { return m_position; }
    constexpr f32 Scale() const { return m_scale; }
    constexpr f32 Rotation() const { return m_rotation; }

    void SetPosition(const vec2& pos) { m_position = pos; }

private:
    State                   m_state;
    core::Game*             m_game;
    utl::vector<Component*> m_components;

    vec2 m_position;
    f32  m_scale{1.0f};
    f32  m_rotation{0.0f};
};

} // namespace retract
