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


#include "Grid.h"


#include "Enemy.h"
#include "Tile.h"
#include "Tower.h"


using namespace retract;

Grid::Grid(core::Game* game) : Entity{ game }
{
    mTiles.resize(num_rows);
    for (auto& tile : mTiles)
    {
        tile.resize(num_cols);
    }

    for (u32 i = 0; i < num_rows; ++i)
    {
        for (u32 j = 0; j < num_cols; ++j)
        {
            mTiles[i][j] = new Tile(game);
            mTiles[i][j]->SetPosition({ tile_size / 2.f + (f32) j * tile_size, start_y + (f32) i * tile_size });
        }
    }

    StartTile()->SetTileState(Tile::TileState::start);
    EndTile()->SetTileState(Tile::TileState::base);

    for (u32 i = 0; i < num_rows; ++i)
    {
        for (u32 j = 0; j < num_cols; ++j)
        {
            if (i > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
            }
            if (i < num_rows - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
            }
            if (j > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
            }
            if (j < num_cols - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
            }
        }
    }

    // find path in reverse
    FindPath(EndTile(), StartTile());
    UpdatePathTiles(StartTile());

    mNextEnemy = enemy_time;
}

void Grid::ProcessClick(i32 x, i32 y)
{
    y -= (i32) (start_y - tile_size / 2.f);
    if (y >= 0)
    {
        x /= (i32) tile_size;
        y /= (i32) tile_size;
        if (x >= 0 && x < (i32) num_cols && y >= 0 && y < (i32) num_rows)
        {
            SelectTile(y, x);
        }
    }
}

bool Grid::FindPath(Tile* start, Tile* goal)
{
    for (u32 i = 0; i < num_rows; ++i)
    {
        for (u32 j = 0; j < num_cols; ++j)
        {
            mTiles[i][j]->g = 0.f;
            mTiles[i][j]->mInOpenSet = false;
            mTiles[i][j]->mInClosedSet = false;
        }
    }

    utl::vector<Tile*> openSet{};

    Tile* current = start;
    current->mInClosedSet = true;

    do
    {
        for(Tile* neighbor : current->mAdjacent)
        {
            if(neighbor->mBlocked)
            {
                continue;
            }

            if(!neighbor->mInClosedSet)
            {
                if(!neighbor->mInOpenSet)
                {
                    // Not in open set, so set parent
                    neighbor->mParent = current;
                    neighbor->h = (neighbor->Position() - goal->Position()).Length();
                    // g(x) is parent's g + cost of traversing edge
                    neighbor->g = current->g + tile_size;
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.emplace_back(neighbor);
                    neighbor->mInOpenSet = true;
                }else
                {
                    // Compute g(x) cost if current becomes parent
                    f32 newg = current->g + tile_size;
                    if(newg < neighbor->g)
                    {
                        neighbor->mParent = current;
                        neighbor->g = newg;
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
            }
        }

        // If open set is empty, all paths are exhausted
        if(openSet.empty()) break;

        // Find lowest cost node in open set
        auto it = std::ranges::min_element(openSet, [](Tile* a, Tile* b) {
            return a->f < b->f;
        });

        current = *it;
        openSet.erase(it);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
    } while(current != goal);

    return current == goal;
}

void Grid::BuildTower()
{
    if (mSelectedTile && !mSelectedTile->mBlocked)
    {
        mSelectedTile->mBlocked = true;
        if (FindPath(EndTile(), StartTile()))
        {
            Tower* t = new Tower(Game());
            t->SetPosition(mSelectedTile->Position());
        } else
        {
            mSelectedTile->mBlocked = false;
            FindPath(EndTile(), StartTile());
        }

        UpdatePathTiles(StartTile());
    }
}

Tile* Grid::StartTile()
{
    return mTiles[3][0];
}

Tile* Grid::EndTile()
{
    return mTiles[3][15];
}

void Grid::UpdateEntity(f32 delta)
{
    mNextEnemy -= delta;
    if (mNextEnemy <= 0.f)
    {
        new Enemy(Game());
        mNextEnemy += enemy_time;
    }
}

void Grid::SelectTile(u64 row, u64 col)
{
    Tile::TileState state = mTiles[row][col]->GetTileState();
    if (state != Tile::TileState::start && state != Tile::TileState::base)
    {
        if (mSelectedTile)
        {
            mSelectedTile->ToggleSelect();
        }
        mSelectedTile = mTiles[row][col];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::UpdatePathTiles(Tile* start)
{
    for (u32 i = 0; i < num_rows; ++i)
    {
        for (u32 j = 0; j < num_cols; ++j)
        {
            if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
            {
                mTiles[i][j]->SetTileState(Tile::TileState::default_state);
            }
        }
    }

    Tile* t = start->mParent;
    while (t != EndTile())
    {
        t->SetTileState(Tile::TileState::path);
        t = t->mParent;
    }
}
