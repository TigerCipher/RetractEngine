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
// File Name: Component
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Common.h"

namespace retract
{
class Entity;

class Component
{
public:
    explicit Component(Entity* owner, i32 update_order = 100);
    virtual ~Component();

    virtual void Update(f32 delta);

    [[nodiscard]] constexpr i32 UpdateOrder() const { return m_update_order; }

protected:
    Entity* m_owner{ nullptr };
    i32     m_update_order{};
};
} // namespace retract::components
