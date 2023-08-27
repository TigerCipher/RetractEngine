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
//  File Name: MeshComponent.h
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Component.h"
#include "Retract/Graphics/Mesh.h"
#include "Retract/Graphics/Shader.h"

namespace retract
{

class MeshComponent : public Component
{
public:
    MeshComponent(Entity* owner);
    ~MeshComponent() override;

    virtual void Draw(Shader* shader);

    virtual void SetMesh(Mesh* mesh) { mMesh = mesh; }
    void SetTextureIndex(u32 index) { mTextureIndex = index; }

private:
    Mesh* mMesh{};
    u32 mTextureIndex{};
};

}