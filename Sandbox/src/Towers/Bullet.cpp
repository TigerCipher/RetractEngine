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
//  File Name: Bullet.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "Bullet.h"

#include "Enemy.h"
#include "Asteroids/Circle.h"
#include "Asteroids/Move.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"
#include "TowerGame.h"

using namespace retract;

Bullet::Bullet(Game* game) : Entity{ game }
{
    Sprite* sc = new Sprite(this);
    sc->SetTexture(game->GetTexture("./Content/Projectile.png"));

    Move* mc = new Move(this);
    mc->SetForwardSpeed(400.f);

    mCircle = new Circle(this);
    mCircle->SetRadius(5.f);
}
void Bullet::UpdateEntity(f32 delta)
{
    for(auto* e : GetGame()->As<TowerGame>()->Enemies())
    {
        if(Intersect(*mCircle, *e->GetCircle()))
        {
            e->SetState(State::dead);
            SetState(State::dead);
            break;
        }
    }

    mLiveTime -= delta;
    if(mLiveTime < 0.f)
    {
        SetState(State::dead);
    }
}
