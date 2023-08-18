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
#include "Background.h"


#include "Retract/Components/Entity.h"

#include <SDL.h>

using namespace retract;

void Background::Update(f32 delta)
{
    Sprite::Update(delta);
    for(auto& bg : m_bg_textures)
    {
        bg.offset.x += m_scroll_speed * delta;
        if(bg.offset.x < -m_screen_size.x)
        {
            bg.offset.x = (f32)(m_bg_textures.size() - 1) * m_screen_size.x - 1;
        }
    }
}
void Background::Draw(SDL_Renderer* renderer)
{
    for (auto& bg : m_bg_textures)
    {
        SDL_Rect r;
        r.w = (i32) m_screen_size.x;
        r.h = (i32) m_screen_size.y;
        r.x = (i32)(m_owner->Position().x - (f32)r.w / 2.f + bg.offset.x);
        r.y = (i32)(m_owner->Position().y - (f32)r.h / 2.f + bg.offset.y);

        SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
    }
}
void Background::SetTextures(const retract::utl::vector<SDL_Texture*>& textures)
{
    i32 count = 0;
    for(auto tex : textures)
    {
        BgTexture temp;
        temp.texture = tex;
        temp.offset.x = (f32)count * m_screen_size.x;
        temp.offset.y = 0;
        m_bg_textures.emplace_back(temp);
        ++count;
    }
}