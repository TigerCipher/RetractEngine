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
//  File Name: Renderer.h
//  Date File Created: 08/25/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Common.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Components/MeshComponent.h"

namespace retract::graphics
{

struct DirectionalLight
{
    vec3 direction{};
    vec3 diffuseColor{};
    vec3 specularColor{};
};

bool Initialize();
void Shutdown();

void AddSprite(Sprite* sprite);
void RemoveSprite(Sprite* sprite);

void AddMesh(MeshComponent* mesh);
void RemoveMesh(MeshComponent* mesh);


void SetViewMatrix(const mat4& view);

void SetAmbientLight(const vec3& ambient);
DirectionalLight& GetDirectionalLight();

void Render();

void DrawIndexed(i32 count);

f32 ScreenWidth();
f32 ScreenHeight();

} // namespace retract::graphics