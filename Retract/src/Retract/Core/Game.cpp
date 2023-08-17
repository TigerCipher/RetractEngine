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

#include "Game.h"

#include "Retract/Types.h"

#include <SDL.h>

#include <iostream>

namespace retract::core
{

bool Game::Initialize()
{
    i32 err = SDL_Init(SDL_INIT_VIDEO);
    if (err)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow("Title here!", 200, 200, 1000, 800, 0);

    if (!m_window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Game::Run()
{
    m_running = true;
    while (m_running)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Shutdown()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: m_running = false; break;
        }
    }
}

void Game::Update() {}
void Game::Render() {}
} // namespace retract::core