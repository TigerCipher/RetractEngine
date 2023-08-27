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
//  File Name: Sandbox.cpp
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Sandbox.h"


#include "Plane.h"
#include "Retract/Components/MeshComponent.h"
#include "Retract/Core/Resources.h"
#include "Retract/Graphics/Renderer.h"

using namespace retract;

void Sandbox::Init()
{
    auto e = DBG_NEW Entity{};
    e->SetPosition({200.f, 75.f, 0.f});
    e->SetScale(100.f);
    quaternion q{math::unity_vec3, -math::half_pi};
    q = math::Concatinate(q, quaternion{math::unitz_vec3, math::pi + math::pi / 4.f});
    e->SetRotation(q);
    MeshComponent* mc = DBG_NEW MeshComponent{e};
    mc->SetMesh(core::GetMesh("./Content/Cube.gpmesh"));

    e = DBG_NEW Entity{};
    e->SetPosition({200.f, -75.f, 0.f});
    e->SetScale(3.f);
    mc = DBG_NEW MeshComponent{e};
    mc->SetMesh(core::GetMesh("./Content/Sphere.gpmesh"));

    constexpr f32 start = -1250.f;
    constexpr f32 size = 250.f;

    // Floor
    for(u32 i = 0; i < 10; ++i)
    {
        for(u32 j = 0; j < 10; ++j)
        {
            e = DBG_NEW Plane{};
            e->SetPosition({start + i * size, start + j * size, -100.f});
        }
    }

    // Left/right walls
    q = quaternion{math::unitx_vec3, math::half_pi};
    for(u32 i = 0; i < 10; ++i)
    {
        e = DBG_NEW Plane{};
        e->SetPosition({start + i * size, start - size, 0.f});
        e->SetRotation(q);

        e = DBG_NEW Plane{};
        e->SetPosition({start + i * size, size - start, 0.f});
        e->SetRotation(q);
    }

    // Forward/back walls
    q = math::Concatinate(q, quaternion{math::unitz_vec3, math::half_pi});
    for(u32 i = 0; i < 10; ++i)
    {
        e = DBG_NEW Plane{};
        e->SetPosition({start - size, start + i * size, 0.f});
        e->SetRotation(q);

        e = DBG_NEW Plane{};
        e->SetPosition({size - start, start + i * size, 0.f});
        e->SetRotation(q);
    }

    // Lighting
    graphics::SetAmbientLight({0.2f, 0.2f, 0.2f});
    graphics::DirectionalLight& dirLight = graphics::GetDirectionalLight();
    dirLight.direction = {0.f, -0.707f, -0.707f};
    dirLight.diffuseColor = {0.78f, 0.88f, 1.f};
    dirLight.specularColor = {0.8f, 0.8f, 0.8f};

    mCamera = DBG_NEW Camera{};

    // Making sure 2d rendering still functions
    e = DBG_NEW Entity{};
    e->SetPosition({-350.f, -350.f, 0.f});
    Sprite* sc = DBG_NEW Sprite{e};
    sc->SetTexture("./Content/HealthBar.png");

    e = DBG_NEW Entity{};
    e->SetPosition({375.f, -275.f, 0.f});
    e->SetScale(0.75f);
    sc = DBG_NEW Sprite{e};
    sc->SetTexture("./Content/Radar.png");

    LOG_DEBUG("Camera pos: {}, {}, {}", mCamera->Position().x, mCamera->Position().y, mCamera->Position().z);
}