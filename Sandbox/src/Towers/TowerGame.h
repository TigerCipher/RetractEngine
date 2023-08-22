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
//  File Name: TowerGame.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Core/Game.h"

class Enemy;
class Grid;

class TowerGame : public retract::Game
{
public:
    void Init() override;
    void ProcessInput(const u8* key_state) override;

    retract::utl::vector<Enemy*>& Enemies() { return mEnemies; }

    Grid* GetGrid() const { return mGrid; }
    Enemy* GetNearestEnemy(const vec2& pos);

private:
    retract::utl::vector<Enemy*> mEnemies{};
    Grid*                        mGrid{ nullptr };
    f32                          mNextEnemy{};
};
