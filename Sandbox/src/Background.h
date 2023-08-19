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
// File Name: Background
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Components/Sprite.h"

class Background : public retract::Sprite
{
public:
    Background(retract::Entity* owner, i32 draw_order = 1) : Sprite{owner, draw_order} {}

    void Update(f32 delta) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetTextures(const retract::utl::vector<SDL_Texture*>& textures);

    void SetScreenSize(const vec2& size) { m_screen_size = size; }
    void SetScrollSpeed(f32 speed) { m_scroll_speed = speed; }
    constexpr f32 ScrollSpeed() const { return m_scroll_speed; }
private:
    struct BgTexture
    {
        SDL_Texture* texture{nullptr};
        vec2 offset{};
    };

    retract::utl::vector<BgTexture> m_bg_textures{};
    vec2 m_screen_size{};
    f32 m_scroll_speed{};
};
