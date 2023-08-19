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
// File Name: Input
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Move.h"

class Input : public Move
{
public:
    Input(retract::Entity* owner) : Move{ owner } {}

    void ProcessInput(const u8* key_state) override;

    [[nodiscard]] constexpr f32 MaxForwardSpeed() const { return mMaxForwardSpeed; }
    void                        SetMaxForwardSpeed(f32 max_forward_speed) { mMaxForwardSpeed = max_forward_speed; }
    [[nodiscard]] constexpr f32 MaxAngularSpeed() const { return mMaxAngularSpeed; }
    void                        SetMaxAngularSpeed(f32 max_angular_speed) { mMaxAngularSpeed = max_angular_speed; }
    [[nodiscard]] constexpr i32 ForwardKey() const { return mForwardKey; }
    void                        SetForwardKey(i32 forward_key) { mForwardKey = forward_key; }
    [[nodiscard]] constexpr i32 BackKey() const { return mBackKey; }
    void                        SetBackKey(i32 back_key) { mBackKey = back_key; }
    [[nodiscard]] constexpr i32 ClockwiseKey() const { return mClockwiseKey; }
    void                        SetClockwiseKey(i32 clockwise_key) { mClockwiseKey = clockwise_key; }
    [[nodiscard]] constexpr i32 CounterClockwiseKey() const { return mCounterClockwiseKey; }
    void SetCounterClockwiseKey(i32 counter_clockwise_key) { mCounterClockwiseKey = counter_clockwise_key; }

private:
    f32 mMaxForwardSpeed{};
    f32 mMaxAngularSpeed{};
    i32 mForwardKey{};
    i32 mBackKey{};
    i32 mClockwiseKey{};
    i32 mCounterClockwiseKey{};
};
