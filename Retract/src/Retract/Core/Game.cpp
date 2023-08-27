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

#include "Retract/Components/Entity.h"
#include "Retract/Components/Sprite.h"
#include "Window.h"
#include "Resources.h"
#include "Retract/Graphics/Renderer.h"
#include "Retract/Graphics/VertexArray.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <ranges>
#include <GL/glew.h>


namespace retract
{

namespace
{
struct FrameInfo
{
    f32 ticks{};
};

FrameInfo          frame_info{};



} // anonymous namespace


Game* Game::mInstance;
bool  Game::mConstructed = false;

bool Game::InitializeInternal()
{
    LOG_TRACE("ReactEngine initializing");
    random::Init();

    if (!window::Init("Test", 1000, 800))
    {
        return false;
    }

    if(!graphics::Initialize())
    {
        return false;
    }

    Init();
    return true;
}

Game::Game()
{
    if (mConstructed)
    {
        LOG_ERROR("Game is already constructed, do not reconstruct");
    } else
    {
        mConstructed = true;
        mInstance    = this;
    }
}

i32 Game::Run()
{
    if (!InitializeInternal())
    {
        LOG_FATAL("ReactEngine failed to initialize");
        return -1;
    }
    m_running = true;
    u32 st    = SDL_GetTicks();
    while (m_running)
    {
        const u32 start_time = SDL_GetTicks();
        ProcessInputInternal();
        Update();
        Render();

        const u32   frame_time = SDL_GetTicks() - start_time;
        f32         fps        = (frame_time > 0) ? 1000.0f / (f32) frame_time : 0.0f;
        std::string title      = std::format("RetractEngine - FPS: {:.5f}", fps);
        window::SetTitle(title);

        const u32 elapsed = SDL_GetTicks() - st;
        if (elapsed >= 1000)
        {
            LOG_TRACE("FPS: {:.5f}", fps);
            st = SDL_GetTicks();
        }
    }

    ShutdownInternal();
    return 0;
}

void Game::ShutdownInternal() const
{
    LOG_TRACE("ReactEngine shutting down");

    // Unload data
    while (!m_entities.empty())
    {
        delete m_entities.back();
    }

    graphics::Shutdown();
    window::Shutdown();
}
void Game::AddEntity(Entity* entity)
{
    if (m_updating_entities)
    {
        m_pending_entities.emplace_back(entity);
    } else
    {
        m_entities.emplace_back(entity);
    }
}
void Game::RemoveEntity(Entity* entity)
{
    auto it = std::ranges::find(m_pending_entities, entity);
    if (it != m_pending_entities.end())
    {
        std::iter_swap(it, m_pending_entities.end() - 1);
        m_pending_entities.pop_back();
    }

    it = std::ranges::find(m_entities, entity);
    if (it != m_entities.end())
    {
        std::iter_swap(it, m_entities.end() - 1);
        m_entities.pop_back();
    }
}


void Game::ProcessInputInternal()
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
    if (key_state[SDL_SCANCODE_ESCAPE])
    {
        m_running = false;
    }

    ProcessInput(key_state);

    m_updating_entities = true;
    for (const auto ent : m_entities)
    {
        ent->ProcessInput(key_state);
    }
    m_updating_entities = false;
}

void Game::Update()
{
    f32 delta        = ((f32) SDL_GetTicks() - frame_info.ticks) / 1000.0f;
    frame_info.ticks = (f32) SDL_GetTicks();

    if (delta > 0.05f)
        delta = 0.0f;

    m_updating_entities = true;
    for (auto* ent : m_entities)
    {
        ent->Update(delta);
    }

    m_updating_entities = false;

    for (auto* pending_ent : m_pending_entities)
    {
        pending_ent->CalculateWorldTransform();
        m_entities.emplace_back(pending_ent);
    }
    m_pending_entities.clear();

    utl::vector<Entity*> dead_entities{};
    for (auto* ent : m_entities)
    {
        if (ent->CurrentState() == Entity::State::dead)
        {
            dead_entities.emplace_back(ent);
        }
    }

    // stuff might need to happen with dead entities?

    for (const auto* ent : dead_entities)
    {
        delete ent;
        ent = nullptr;
    }
}

void Game::Render() const
{
    graphics::Render();
    window::SwapBuffers();
}

} // namespace retract