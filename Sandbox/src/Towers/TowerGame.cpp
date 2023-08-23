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


#include "TowerGame.h"


#include "AIComponent.h"
#include "AIState.h"
#include "Enemy.h"
#include "Grid.h"

#include <SDL2/SDL.h>

using namespace retract;

void TowerGame::Init()
{
    mGrid = new Grid();

    // For testing AIComponent
    //Entity* a = new Entity(this);
    //AIComponent* aic = new AIComponent(a);
    ////// Register states with AIComponent
    //aic->RegisterState(new AIPatrol(aic));
    //aic->RegisterState(new AIDeath(aic));
    //aic->RegisterState(new AIAttack(aic));
    ////// Start in patrol state
    //aic->ChangeState("Patrol");
}
void TowerGame::ProcessInput(const u8* key_state)
{
    if(key_state[SDL_SCANCODE_B])
    {
        mGrid->BuildTower();
    }

    i32 x, y;
    u32 buttons = SDL_GetMouseState(&x, &y);
    if(SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
    {
        mGrid->ProcessClick(x, y);
    }
}

Enemy* TowerGame::GetNearestEnemy(const vec2& pos)
{
    Enemy* best{ nullptr };
    if (!mEnemies.empty())
    {
        best           = mEnemies[0];
        f32 bestDistSq = (pos - mEnemies[0]->Position()).LengthSq();
        for (u32 i = 1; i < mEnemies.size(); ++i)
        {
            const f32 newDistSq = (pos - mEnemies[i]->Position()).LengthSq();
            if (newDistSq < bestDistSq)
            {
                bestDistSq = newDistSq;
                best       = mEnemies[i];
            }
        }
    }

    return best;
}