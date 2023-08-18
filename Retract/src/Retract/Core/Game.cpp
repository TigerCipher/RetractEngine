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

#include <SDL.h>
#include <SDL_image.h>

#include <algorithm>


namespace retract::core
{

namespace
{
struct FrameInfo
{
    f32 ticks{};
};

FrameInfo frame_info{};
} // anonymous namespace

bool Game::InitializeInternal()
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
    if (!m_renderer)
    {
        LOG_ERROR("Failed to create renderer: {}", SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        LOG_ERROR("Failed to initialize SDL Image");
        return false;
    }

    Init();
    return true;
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
        ProcessInput();
        Update();
        Render();

        const u32   frame_time = SDL_GetTicks() - start_time;
        f32         fps        = (frame_time > 0) ? 1000.0f / (f32)frame_time : 0.0f;
        std::string title      = std::format("RetractEngine - FPS: {:.5f}", fps);
        SDL_SetWindowTitle(m_window, title.c_str());

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

void Game::ShutdownInternal()
{
    LOG_TRACE("ReactEngine shutting down");
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
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
    LOG_INFO("Removing entity");
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
void Game::AddSprite(Sprite* sprite)
{
    const i32 draw_order = sprite->DrawOrder();
    auto      it         = m_sprites.begin();
    while (it != m_sprites.end())
    {
        if (draw_order < (*it)->DrawOrder())
            break;
        ++it;
    }

    m_sprites.insert(it, sprite);
}

void Game::RemoveSprite(Sprite* sprite)
{
    auto it = std::ranges::find(m_sprites, sprite);
    m_sprites.erase(it);
}

SDL_Texture* Game::GetTexture(const char* filename)
{
    if (m_textures.contains(filename))
    {
        return m_textures[filename];
    }

    SDL_Texture* tex     = LoadTexture(filename);
    m_textures[filename] = tex;
    return tex;
}

SDL_Texture* Game::LoadTexture(const char* filename)
{
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf)
    {
        LOG_ERROR("Failed to load texture file: {}", filename);
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    if (!tex)
    {
        LOG_ERROR("Failed to convert surface to texture from {}", filename);
        return nullptr;
    }

    return tex;
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
    if (key_state[SDL_SCANCODE_ESCAPE])
    {
        m_running = false;
    }
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

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 52, 15, 15, 255);
    SDL_RenderClear(m_renderer);

    for (auto* spr : m_sprites)
    {
        spr->Draw(m_renderer);
    }

    SDL_RenderPresent(m_renderer);
}
} // namespace retract::core