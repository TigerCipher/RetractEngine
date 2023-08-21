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
//  File Name: Nav.h
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------


#include "Nav.h"


#include "Tile.h"
#include "Retract/Components/Entity.h"

using namespace retract;

void Nav::Update(f32 delta)
{
    if (mNextNode)
    {
        vec2 diff = m_owner->Position() - mNextNode->Position();
        if (math::NearZero(diff.Length(), 2.f))
        {
            mNextNode = mNextNode->Parent();
            TurnTo(mNextNode->Position());
        }
    }

    Move::Update(delta);
}

void Nav::StartPath(Tile* start)
{
    mNextNode = start->Parent();
    TurnTo(mNextNode->Position());
}

void Nav::TurnTo(const vec2& pos)
{
    const vec2 dir   = pos - m_owner->Position();
    const f32  angle = math::Atan2(-dir.y, dir.x);
    m_owner->SetRotation(angle);
}
