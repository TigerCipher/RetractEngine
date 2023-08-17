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
// File Name: Game
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "Retract/Common.h"

struct SDL_Window;
struct SDL_Renderer;

namespace retract::core
{

class Game
{
public:
    Game() = default;
    virtual ~Game() = default;

    bool Initialize();
    i32 Run(); // returns 0 if no issues
    void Shutdown() const;

    virtual void Init() = 0;
private:
    void ProcessInput();
    void Update();
    void Render();

    bool m_running{false};
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr}; // TODO: Testing purposes only
};

}
