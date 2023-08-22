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
// File Name: Asteroid
// Date File Created: 08/19/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Asteroid.h"
#include "AsteroidGame.h"

using namespace retract;

Asteroid::Asteroid(Game* game) : Entity{ game }
{
    vec2 pos = retract::random::Vector(retract::math::zero_vec2, { 1000, 800 });
    SetPosition(pos);
    SetRotation(retract::random::Float(0.f, retract::math::two_pi));
    m_sprite = new retract::Sprite(this);
    m_sprite->SetTexture(game->GetTexture("./Content/asteroid.png"));

    m_circle = new Circle(this);
    m_circle->SetRadius(32.f);

    mc = new Move(this);
    mc->SetForwardSpeed(150.f);
    dynamic_cast<AsteroidGame*>(game)->AddAsteroid(this);
}
Asteroid::~Asteroid()
{
    dynamic_cast<AsteroidGame*>(GetGame())->RemoveAsteroid(this);
}