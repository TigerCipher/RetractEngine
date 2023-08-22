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
// File Name: AsteroidGame
// Date File Created: 08/19/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "AsteroidGame.h"


#include "Asteroid.h"
#include "Background.h"


void AsteroidGame::Init()
{
    LOG_INFO("AsteroidGame initialized");
    //asteroid = new Asteroid(this);
    //AddEntity(asteroid);

    ship = new Ship();
    ship->SetPosition({ 100.f, 384.f });


    auto* temp = new retract::Entity();
    temp->SetPosition({ 512, 400 });
    auto* bg = new Background(temp);
    bg->SetScreenSize({ 1000, 800 });
    retract::utl::vector<SDL_Texture*> bgtex{
        GetTexture("./Content/bg01.png"),
        GetTexture("./Content/bg02.png"),
    };
    bg->SetTextures(bgtex);
    bg->SetScrollSpeed(-100.f);

    bg = new Background(temp, 50);
    bg->SetScreenSize({ 1000, 800 });
    bgtex.clear();
    bgtex.emplace_back(GetTexture("./Content/stars.png"));
    bgtex.emplace_back(GetTexture("./Content/stars.png"));
    bg->SetTextures(bgtex);
    bg->SetScrollSpeed(-200.f);

    constexpr u32 numAsteroids = 20;
    for (u32 i = 0; i < numAsteroids; ++i)
    {
        new Asteroid();
    }
}
void AsteroidGame::AddAsteroid(Asteroid* asteroid)
{
    asteroids.emplace_back(asteroid);
}
void AsteroidGame::RemoveAsteroid(Asteroid* asteroid)
{
    auto iter = std::ranges::find(asteroids, asteroid);
    if (iter != asteroids.end())
    {
        asteroids.erase(iter);
    }
}
