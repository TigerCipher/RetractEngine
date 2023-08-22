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
//  File Name: Tower.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------


#include "Tower.h"


#include "Bullet.h"
#include "Enemy.h"
#include "TowerGame.h"
#include "Asteroids/Move.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"

using namespace retract;

Tower::Tower()
{
    Sprite* sc = new Sprite(this, 200);
    sc->SetTexture("./Content/Tower.png");

    mMove = new Move(this);

    mNextAttack = attack_time;
}
void Tower::UpdateEntity(f32 delta)
{
    mNextAttack -= delta;
    if(mNextAttack <= 0.f)
    {
        Enemy* e = Game::As<TowerGame>()->GetNearestEnemy(Position());
        if(e)
        {
            vec2 dir = e->Position() - Position();
            f32 dist = dir.Length();
            if(dist < attack_range)
            {
                SetRotation(math::Atan2(-dir.y, dir.x));
                Bullet* b = new Bullet();
                b->SetPosition(Position());
                b->SetRotation(Rotation());
            }
        }
        mNextAttack += attack_time;
    }
}