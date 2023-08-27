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


#include "VertexArray.h"


#include <GL/glew.h>

namespace retract
{
VertexArray::VertexArray(const std::vector<f32>& vertices, u32 num_verts, const std::vector<u32>& indices)
{
    mNumVerts   = num_verts;
    mNumIndices = (u32) indices.size();

    glGenVertexArrays(1, &mVao);
    glCreateVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // Vertex buffer
    glCreateBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, num_verts * 8 * sizeof(f32), vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glCreateBuffers(1, &mIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(u32), indices.data(), GL_STATIC_DRAW);

    // Vertex attributes (for now assuming only one vertex format)

    // Position is 3 floats
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 8, nullptr);

    // Normal is 3 floats
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 8, reinterpret_cast<void*>(sizeof(f32) * 3));

    // Tex coords are 2 floats
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(f32) * 8, reinterpret_cast<void*>(sizeof(f32) * 6));
}

VertexArray::~VertexArray()
{
    LOG_WARN("Deleting vao");
    glDeleteBuffers(1, &mVbo);
    glDeleteBuffers(1, &mIbo);
    glDeleteVertexArrays(1, &mVao);
}

void VertexArray::Activate() const
{
    glBindVertexArray(mVao);
}

} // namespace retract