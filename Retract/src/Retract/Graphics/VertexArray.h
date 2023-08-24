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
//  File Name: VertexArray.h
//  Date File Created: 08/24/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Common.h"

namespace retract
{

class VertexArray
{
public:
    VertexArray(const std::vector<f32>& vertices, u32 num_verts, const std::vector<u32>& indices);
    ~VertexArray();

    void Activate() const;

    constexpr u32 NumVerts() const { return mNumVerts; }
    constexpr u32 NumIndices() const { return mNumIndices; }
private:
    u32 mNumVerts{};
    u32 mNumIndices{};
    u32 mVbo{};
    u32 mIbo{};
    u32 mVao{};
};

} // namespace retract
