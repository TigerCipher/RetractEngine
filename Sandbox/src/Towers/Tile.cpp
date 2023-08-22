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


#include "Tile.h"


#include "Retract/Components/Sprite.h"
#include "Retract/Core/Game.h"

using namespace retract;

Tile::Tile()
{
    mSprite = new Sprite(this);
    UpdateTexture();
}

void Tile::SetTileState(TileState tile_state)
{
    mTileState = tile_state;
    UpdateTexture();
}

void Tile::ToggleSelect()
{
    mSelected = !mSelected;
    UpdateTexture();
}

void Tile::UpdateTexture()
{
    std::string filename{};
    switch (mTileState)
    {
    case TileState::path:
        if (mSelected)
            filename = "./Content/TileGreySelected.png";
        else
            filename = "./Content/TileGrey.png";
        break;
    case TileState::start: filename = "./Content/TileTan.png"; break;
    case TileState::base: filename = "./Content/TileGreen.png"; break;
    default:
        if (mSelected)
            filename = "./Content/TileBrownSelected.png";
        else
            filename = "./Content/TileBrown.png";
        break;
    }

    mSprite->SetTexture(filename.c_str());
}