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
// File Name: Sprite
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Common.h"
#include "Component.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace retract
{
class Entity;

class Sprite : public Component
{
public:
    Sprite(Entity* owner, i32 draw_order = 100);
    virtual ~Sprite();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    [[nodiscard]] constexpr i32 DrawOrder() const { return m_draw_order; }
    [[nodiscard]] constexpr i32 Width() const { return m_width; }
    [[nodiscard]] constexpr i32 Height() const { return m_height; }

protected:
    i32          m_draw_order{ 100 };
    SDL_Texture* m_texture{ nullptr };
    i32          m_width{ 0 };
    i32          m_height{ 0 };
};

} // namespace retract
