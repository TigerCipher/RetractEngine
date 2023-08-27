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
#include "Retract/Core/Resources.h"
#include "Retract/Graphics/Renderer.h"

namespace retract
{


Sprite::Sprite(Entity* owner, i32 draw_order) : Component{ owner }, mDrawOrder{ draw_order }
{
    graphics::AddSprite(this);
}

Sprite::~Sprite()
{
    graphics::RemoveSprite(this);
}

void Sprite::Draw(Shader* shader)
{
    if (!mTexture)
        return;

    const mat4 scale = math::Scale((f32) mWidth, (f32) mHeight, 1.f);
    const mat4 world = scale * mOwner->WorldTransform();

    // All sprites use the same shader, so the shader is set active elsewhere

    shader->SetMatrix("WorldTransform", world);
    mTexture->Activate();

    graphics::DrawIndexed(6);
}

void Sprite::SetTexture(Texture* texture)
{
    mTexture = texture;
    mWidth   = texture->Width();
    mHeight  = texture->Height();
}

void Sprite::SetTexture(const char* filename)
{
    mTexture = core::GetTexture(filename);
    if (mTexture)
    {
        mWidth  = mTexture->Width();
        mHeight = mTexture->Height();
    }
}


void AnimatedSprite::Update(f32 delta)
{
    Sprite::Update(delta);

    if (mTextures.empty())
        return;

    mCurrentFrame += mFps * delta;
    while (mCurrentFrame >= (f32) mTextures.size())
    {
        mCurrentFrame -= (f32) mTextures.size();
    }
    SetTexture(mTextures[(u32) mCurrentFrame]);
}


void AnimatedSprite::SetTextures(const utl::vector<const char*>& filenames)
{
    for (const auto f : filenames)
    {
        mTextures.emplace_back(core::GetTexture(f));
    }

    mCurrentFrame = 0.f;
    SetTexture(mTextures[0]);
}

} // namespace retract