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
// File Name: Laser
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Laser.h"


#include "Circle.h"
#include "Move.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"

#include "Asteroid.h"
#include "AsteroidGame.h"

using namespace retract;

Laser::Laser()
{
    Sprite* sc = new Sprite(this, 5);
    sc->SetTexture("./Content/Laser.png");

    Move* mc = new Move(this);
    mc->SetForwardSpeed(800.f);

    mCircle = new Circle(this);
    mCircle->SetRadius(11.f);
}

void Laser::UpdateEntity(f32 delta)
{
    mDeathTimer -= delta;
    if (mDeathTimer <= 0.f)
    {
        SetState(State::dead);
    } else
    {
        for (const auto ast : Game::As<AsteroidGame>()->Asteroids())
        {
            if (Intersect(*mCircle, *ast->GetCircle()))
            {
                SetState(State::dead);
                ast->SetState(State::dead);
                break;
            }
        }
    }
}
