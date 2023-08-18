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

#include "Entity.h"

#include "Component.h"
#include "Retract/Core/Game.h"

namespace retract
{

Entity::Entity(core::Game* game) : m_state{State::active}, m_game{game}
{
    game->AddEntity(this);
}

Entity::~Entity()
{
    LOG_WARN("Deleting entity");
    m_game->RemoveEntity(this);
    while(!m_components.empty())
    {
        auto& comp = m_components.back();
        delete comp;
        comp = nullptr;
    }
}
void Entity::Update(f32 delta)
{
    if(m_state != State::active) return;
    UpdateComponents(delta);
    UpdateEntity(delta);
}

void Entity::UpdateComponents(f32 delta)
{
    for(auto* comp : m_components)
    {
        comp->Update(delta);
    }
}

void Entity::UpdateEntity(f32 delta) {}

void Entity::AddComponent(Component* comp)
{
    LOG_INFO("Add comp");
    i32 order = comp->UpdateOrder();
    auto it = m_components.begin();
    LOG_INFO("Inc iter");
    while(it != m_components.end())
    {
        if(order < (*it)->UpdateOrder()) break;
        ++it;
    }

    m_components.insert(it, comp);
}

void Entity::RemoveComponent(Component* comp)
{
    LOG_INFO("Remove comp");
    auto it = std::ranges::find(m_components, comp);
    if(it != m_components.end())
    {
        //delete *it; // this method is called by Component dtor, deleting here might cause weirdness. Entity dtor will delete component
        m_components.erase(it);
    }
}

}