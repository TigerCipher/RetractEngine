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
//  File Name: Enemy.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "Enemy.h"


#include "Grid.h"
#include "Nav.h"
#include "Tile.h"
#include "Asteroids/Circle.h"
#include "TowerGame.h"
#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"

using namespace retract;

Enemy::Enemy()
{
    Game::As<TowerGame>()->Enemies().emplace_back(this);

    Sprite* sc = new Sprite(this);
    sc->SetTexture("./Content/Airplane.png");

    SetPosition(Game::As<TowerGame>()->GetGrid()->StartTile()->Position());

    Nav* nav = new Nav(this);
    nav->SetForwardSpeed(200.f);
    nav->StartPath(Game::As<TowerGame>()->GetGrid()->StartTile());


    mCircle = new Circle(this);
    mCircle->SetRadius(25.f);
}
Enemy::~Enemy()
{
    auto it = std::ranges::find(Game::As<TowerGame>()->Enemies(), this);
    Game::As<TowerGame>()->Enemies().erase(it);
}

void Enemy::UpdateEntity(f32 delta)
{
    Entity::UpdateEntity(delta);

    vec2 diff = Position() - Game::As<TowerGame>()->GetGrid()->EndTile()->Position();
    if(math::NearZero(diff.Length(), 10.f))
    {
        SetState(State::dead);
    }
}