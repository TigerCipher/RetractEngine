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
//  File Name: Camera.cpp
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Camera.h"


#include "Retract/Graphics/Renderer.h"
#include <SDL2/SDL.h>

using namespace retract;

Camera::Camera()
{
    mMove = DBG_NEW MoveComponent{ this };
}

void Camera::UpdateEntity(f32 delta)
{
    const vec3     camPos = Position();
    const vec3     target = camPos + Forward() * 100.f;
    constexpr vec3 up     = math::unitz_vec3;

    const mat4 view = math::LookAt(camPos, target, up);
    graphics::SetViewMatrix(view);
}
void Camera::EntityInput(const u8* keys)
{
    f32 forward{};
    f32 angular{};

    if (keys[SDL_SCANCODE_W])
    {
        forward += 300.f;
    }
    if (keys[SDL_SCANCODE_S])
    {
        forward -= 300.f;
    }
    if (keys[SDL_SCANCODE_A])
    {
        angular -= math::two_pi;
    }
    if (keys[SDL_SCANCODE_D])
    {
        angular += math::two_pi;
    }

    mMove->SetForwardSpeed(forward);
    mMove->SetAngularSpeed(angular);
}
