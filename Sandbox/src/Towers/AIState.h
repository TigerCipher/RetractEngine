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
// File Name: AIState
// Date File Created: 08/20/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Retract/Common.h"

class AIComponent;

class AIState
{
public:
    AIState(AIComponent* owner) : mOwner{owner} {}
    virtual ~AIState() = default;

    virtual void Update(f32 delta) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;

    virtual const char* Name() const = 0;

protected:
    AIComponent* mOwner;
};

class AIPatrol : public AIState
{
public:
    AIPatrol(AIComponent* owner) : AIState{ owner } {}
    void        Update(f32 delta) override;
    void        OnEnter() override;
    void        OnExit() override;
    const char* Name() const override { return "Patrol"; }
};

class AIDeath : public AIState
{
public:
    AIDeath(AIComponent* owner) : AIState{ owner } {}
    void        Update(f32 delta) override;
    void        OnEnter() override;
    void        OnExit() override;
    const char* Name() const override { return "Death"; }
};

class AIAttack : public AIState
{
public:
    AIAttack(AIComponent* owner) : AIState{ owner } {}
    void        Update(f32 delta) override;
    void        OnEnter() override;
    void        OnExit() override;
    const char* Name() const override { return "Attack"; }
};