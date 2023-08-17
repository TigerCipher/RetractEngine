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

#include <SDL.h>


namespace retract::core
{

bool Game::Initialize()
{
    LOG_TRACE("ReactEngine initializing");
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        LOG_ERROR("Failed to initialize SDL: {}", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("Title here!", 200, 200, 1000, 800, 0);

    if (!m_window)
    {
        LOG_ERROR("Failed to create window: {}", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!m_renderer)
    {
        LOG_ERROR("Failed to create renderer: {}", SDL_GetError());
        return false;
    }

    Init();
    return true;
}

i32 Game::Run()
{
    if(!Initialize())
    {
        LOG_FATAL("ReactEngine failed to initialize");
        return -1;
    }
    m_running = true;
    while (m_running)
    {
        ProcessInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}

void Game::Shutdown() const
{
    LOG_TRACE("ReactEngine shutting down");
    SDL_DestroyRenderer(m_renderer);
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

    const u8* key_state = SDL_GetKeyboardState(nullptr);
    if(key_state[SDL_SCANCODE_ESCAPE])
    {
        m_running = false;
    }
}

void Game::Update() {}
void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 52, 15, 15, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}
} // namespace retract::core