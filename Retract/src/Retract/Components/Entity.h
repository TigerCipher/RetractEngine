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

    explicit Entity();
    virtual ~Entity();

    void Update(f32 delta);
    void UpdateComponents(f32 delta) const;

    virtual void UpdateEntity(f32 delta) {}

    void         ProcessInput(const u8* key_state);
    virtual void EntityInput(const u8* key_state) {}

    void AddComponent(Component* comp);
    void RemoveComponent(Component* comp);

    constexpr State CurrentState() const { return mState; }
    void            SetState(State state) { mState = state; }


    void           CalculateWorldTransform();
    const mat4&    WorldTransform() const { return mWorldTransform; }
    constexpr vec2 Position() const { return mPosition; }
    constexpr f32  Scale() const { return mScale; }
    constexpr f32  Rotation() const { return mRotation; }

    void SetPosition(const vec2& pos)
    {
        mPosition             = pos;
        mRecalculateTransform = true;
    }
    void SetScale(const f32 scale)
    {
        mScale                = scale;
        mRecalculateTransform = true;
    }
    void SetRotation(const f32 rotation)
    {
        mRotation             = rotation;
        mRecalculateTransform = true;
    }

    vec2 Forward() const { return { math::Cos(mRotation), -math::Sin(mRotation) }; }


private:
    State                   mState;
    utl::vector<Component*> mComponents;

    mat4 mWorldTransform{};
    bool mRecalculateTransform{ true };

    vec2 mPosition;
    f32  mScale{ 1.f };
    f32  mRotation{};
};

} // namespace retract
