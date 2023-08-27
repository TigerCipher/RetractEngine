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

Entity::Entity() : mState{ State::active }
{
    Game::Instance()->AddEntity(this);
}

Entity::~Entity()
{
    Game::Instance()->RemoveEntity(this);
    while (!mComponents.empty())
    {
        auto& comp = mComponents.back();
        delete comp;
        comp = nullptr;
    }
}
void Entity::Update(f32 delta)
{
    if (mState != State::active)
        return;

    CalculateWorldTransform();

    UpdateComponents(delta);
    UpdateEntity(delta);

    CalculateWorldTransform();
}

void Entity::UpdateComponents(f32 delta) const
{
    for (auto* comp : mComponents)
    {
        comp->Update(delta);
    }
}
void Entity::ProcessInput(const u8* key_state)
{
    if (mState != State::active)
        return;

    for (const auto comp : mComponents)
    {
        comp->ProcessInput(key_state);
    }

    EntityInput(key_state);
}


void Entity::AddComponent(Component* comp)
{
    const i32  order = comp->UpdateOrder();
    auto it    = mComponents.begin();
    while (it != mComponents.end())
    {
        if (order < (*it)->UpdateOrder())
            break;
        ++it;
    }

    mComponents.insert(it, comp);
}

void Entity::RemoveComponent(Component* comp)
{
    if (const auto it = std::ranges::find(mComponents, comp); it != mComponents.end())
    {
        mComponents.erase(it);
    }
}

void Entity::CalculateWorldTransform()
{
    if (!mRecalculateTransform)
        return;

    mRecalculateTransform = false;
    // Scale, rotate, translate
    mWorldTransform = math::Scale(mScale);
    mWorldTransform *= math::FromQuaternion(mRotation);
    mWorldTransform *= math::Translation(mPosition);

    for (const auto comp : mComponents)
    {
        comp->OnUpdateWorldTransform();
    }
}

} // namespace retract