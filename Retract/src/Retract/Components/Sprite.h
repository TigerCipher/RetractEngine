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
#include "Retract/Graphics/Shader.h"
#include "Retract/Graphics/Texture.h"

namespace retract
{
class Entity;

class Sprite : public Component
{
public:
    Sprite(Entity* owner, i32 draw_order = 100);
    ~Sprite() override;

    virtual void Draw(Shader* shader);
    virtual void SetTexture(Texture* texture);
    virtual void SetTexture(const char* filename);

    [[nodiscard]] constexpr i32 DrawOrder() const { return mDrawOrder; }
    [[nodiscard]] constexpr i32 Width() const { return mWidth; }
    [[nodiscard]] constexpr i32 Height() const { return mHeight; }

protected:
    i32      mDrawOrder{ 100 };
    Texture* mTexture{ nullptr };
    i32      mWidth{ 0 };
    i32      mHeight{ 0 };
};

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite(Entity* owner, i32 draw_order = 100) : Sprite(owner, draw_order) {}

    void Update(f32 delta) override;

    void SetTextures(const std::vector<const char*>& filenames);

    constexpr f32 Fps() const { return mFps; }
    void          SetFps(f32 fps) { mFps = fps; }

private:
    std::vector<Texture*> mTextures{};
    f32                   mCurrentFrame{};
    f32                   mFps{ 24.0f };
};

} // namespace retract
