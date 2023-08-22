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

using namespace retract;
Ship::Ship(Game* game) : Entity{ game }
{
    AnimatedSprite*           anim  = new AnimatedSprite(this, 150);
    utl::vector<SDL_Texture*> anims = {
        game->GetTexture("./Content/ship01.png"),
        game->GetTexture("./Content/ship02.png"),
        game->GetTexture("./Content/ship03.png"),
        game->GetTexture("./Content/ship04.png"),
    };
    anim->SetTextures(anims);

    Input* ic = new Input(this);
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
    if(key_state[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.f)
    {
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(Position());
        laser->SetRotation(Rotation());

        mLaserCooldown = 0.5f;
    }
}