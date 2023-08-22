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
//  File Name: Tile.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Components/Entity.h"

namespace retract
{
class Sprite;
}

class Tile : public retract::Entity
{
public:
    friend class Grid;
    enum class TileState
    {
        default_state,
        path,
        start,
        base,
    };

    Tile(retract::Game* game);

    TileState GetTileState() const { return mTileState; }
    void      SetTileState(TileState tile_state);

    const Tile* Parent() const { return mParent; }

    void ToggleSelect();

private:
    retract::utl::vector<Tile*> mAdjacent{};
    Tile*                       mParent{};
    f32                         f{};
    f32                         g{};
    f32                         h{};
    bool                        mInOpenSet{};
    bool                        mInClosedSet{};
    bool                        mBlocked{};
    retract::Sprite*            mSprite{};
    TileState                   mTileState{ TileState::default_state };
    bool                        mSelected{};

    void UpdateTexture();
};
