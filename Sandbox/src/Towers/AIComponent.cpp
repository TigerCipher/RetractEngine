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
// File Name: AIComponent
// Date File Created: 08/20/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "AIComponent.h"


#include "AIState.h"


void AIComponent::Update(f32 delta)
{
    if(mCurrentState)
    {
        mCurrentState->Update(delta);
    }
}

void AIComponent::ChangeState(const std::string& name)
{
    if(mCurrentState)
    {
        mCurrentState->OnExit();
    }

    auto it = mStateMap.find(name);
    if(it != mStateMap.end())
    {
        mCurrentState = it->second;
        mCurrentState->OnEnter();
    }else
    {
        LOG_WARN("Could not find AIState {} in the state map", name);
        mCurrentState = nullptr;
    }
}

void AIComponent::RegisterState(AIState* state)
{
    mStateMap.emplace(state->Name(), state);
}
