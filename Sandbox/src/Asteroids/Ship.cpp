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
// File Name: Ship
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Ship.h"

#include "Input.h"
#include "Laser.h"
#include "Retract/Core/Game.h"
#include "Retract/Components/Sprite.h"

#include <SDL2/SDL.h>

using namespace retract;
Ship::Ship()
{
    auto* anim = new AnimatedSprite(this, 150);

    const utl::vector<const char*> anims = {
        "./Content/ship01.png",
        "./Content/ship02.png",
        "./Content/ship03.png",
        "./Content/ship04.png",
    };
    anim->SetTextures(anims);

    auto* ic = new Input(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    ic->SetMaxForwardSpeed(300.0f);
    ic->SetMaxAngularSpeed(math::two_pi);
}
void Ship::UpdateEntity(f32 delta)
{
    mLaserCooldown -= delta;
}


void Ship::EntityInput(const u8* key_state)
{
    if (key_state[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.f)
    {
        Laser* laser = new Laser();
        laser->SetPosition(Position());
        laser->SetRotation(Rotation());

        mLaserCooldown = 0.5f;
    }
}