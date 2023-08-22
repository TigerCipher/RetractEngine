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

#include "Sprite.h"

#include "Entity.h"
#include "Retract/Core/Game.h"

#include <SDL.h>

namespace retract
{


Sprite::Sprite(Entity* owner, i32 draw_order) : Component{owner}, m_draw_order{draw_order}
{
    owner->GetGame()->AddSprite(this);
}

Sprite::~Sprite()
{
    m_owner->GetGame()->RemoveSprite(this);
}

void Sprite::Draw(SDL_Renderer* renderer)
{
    if(!m_texture) return;

    SDL_Rect r;
    r.w = (i32)(m_width * m_owner->Scale());
    r.h = (i32)(m_height * m_owner->Scale());
    r.x = (i32) (m_owner->Position().x - (f32)r.w / 2.0f);
    r.y = (i32) (m_owner->Position().y - (f32)r.h / 2.0f);

    SDL_RenderCopyEx(renderer, m_texture, nullptr, &r, -math::ToDegrees(m_owner->Rotation()), nullptr, SDL_FLIP_NONE);
}

void Sprite::SetTexture(SDL_Texture* texture)
{
    m_texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &m_width, &m_height);
}


void AnimatedSprite::Update(f32 delta)
{
    Sprite::Update(delta);

    if(m_textures.empty()) return;

    m_current_frame += m_fps * delta;
    while(m_current_frame >= (f32)m_textures.size())
    {
        m_current_frame -= (f32) m_textures.size();
    }
    SetTexture(m_textures[(u32)m_current_frame]);
}

void AnimatedSprite::SetTextures(const utl::vector<SDL_Texture*>& textures)
{
    m_textures = textures;
    if(m_textures.empty()) return;
    m_current_frame = 0.0f;
    SetTexture(m_textures[0]);
}

}