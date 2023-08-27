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
//  File Name: MeshComponent.cpp
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "MeshComponent.h"

#include "Entity.h"
#include "Retract/Graphics/Renderer.h"

namespace retract
{

MeshComponent::MeshComponent(Entity* owner) : Component{owner}
{
    graphics::AddMesh(this);
}

MeshComponent::~MeshComponent()
{
    graphics::RemoveMesh(this);
}

void MeshComponent::Draw(Shader* shader)
{
    if(!mMesh) return;

    shader->SetMatrix("WorldTransform", mOwner->WorldTransform());
    shader->SetFloat("SpecularPower", mMesh->SpecularPower());

    if (const Texture* t = mMesh->GetTexture(mTextureIndex))
    {
        t->Activate();
    }

    const VertexArray* vao = mMesh->GetVertexArray();
    vao->Activate();

    graphics::DrawIndexed((i32)vao->NumIndices());
}

}