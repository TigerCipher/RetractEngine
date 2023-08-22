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
//  File Name: Grid.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Components/Entity.h"

class Tile;

class Grid : public retract::Entity
{
public:
    Grid(retract::Game* game);

    void ProcessClick(i32 x, i32 y);
    bool FindPath(Tile* start, Tile* goal);
    void BuildTower();

    Tile* StartTile();
    Tile* EndTile();

    void UpdateEntity(f32 delta) override;

private:
    void SelectTile(u64 row, u64 col);
    void UpdatePathTiles(Tile* start);


    Tile*                                             mSelectedTile{};
    retract::utl::vector<retract::utl::vector<Tile*>> mTiles{};
    f32                                               mNextEnemy{};

    const u64 num_rows = 7;
    const u64 num_cols = 16;
    const f32 start_y    = 192.f;
    const f32 tile_size  = 64.f;
    const f32 enemy_time = 1.5f;
};
