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
//  File Name: AIState.cpp
//  Date File Created: 08/20/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "AIState.h"
#include "AIComponent.h"

void AIPatrol::Update(f32 delta)
{
    LOG_TRACE("Updating {} state", Name());
    if constexpr (true)
    {
        mOwner->ChangeState("Death");
    }
}

void AIPatrol::OnEnter()
{
    LOG_TRACE("Entering {} state", Name());
}
void AIPatrol::OnExit()
{
    LOG_TRACE("Exiting {} state", Name());
}

void AIDeath::Update(f32 delta)
{
    LOG_TRACE("Updating {} state", Name());
}

void AIDeath::OnEnter()
{
    LOG_TRACE("Entering {} state", Name());
}
void AIDeath::OnExit()
{
    LOG_TRACE("Exiting {} state", Name());
}

void AIAttack::Update(f32 delta)
{
    LOG_TRACE("Updating {} state", Name());
}

void AIAttack::OnEnter()
{
    LOG_TRACE("Entering {} state", Name());
}
void AIAttack::OnExit()
{
    LOG_TRACE("Exiting {} state", Name());
}
