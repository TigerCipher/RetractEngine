//  ------------------------------------------------------------------------------
//
//  RetractEngine
//     Copyright 2023 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  File Name: Mesh.h
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Texture.h"
#include "VertexArray.h"
#include "Retract/Common.h"

namespace retract
{

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    bool Load(const std::string& filename);
    void Unload();

    Texture* GetTexture(u32 index) const;

    constexpr VertexArray* GetVertexArray() const { return mVertexArray; }

    constexpr const std::string& ShaderName() const { return mShaderName; }
    constexpr f32                Radius() const { return mRadius; }
    constexpr f32                SpecularPower() const { return mSpecularPower; }

private:
    std::vector<Texture*> mTextures{};
    VertexArray*          mVertexArray{};
    std::string           mShaderName{};
    f32                   mRadius{};
    f32                   mSpecularPower{100.f};
};

} // namespace retract