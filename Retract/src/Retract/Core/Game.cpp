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
ref<Shader>        sprite_shader{};
scope<VertexArray> sprite_verts{};

void CreateSpriteVerts()
{
    std::vector<f32> vertices{
        -0.5f, 0.5f,  0.f, 0.f, 0.f, // top left
        0.5f,  0.5f,  0.f, 1.f, 0.f, // top right
        0.5f,  -0.5f, 0.f, 1.f, 1.f, // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
    };

    std::vector<u32> indices{ 0, 1, 2, 2, 3, 0 };

    sprite_verts = CreateScope<VertexArray>(vertices, 4, indices);
}

bool LoadShaders()
{
    sprite_shader = core::LoadShader("Sprite", "./Shaders/Sprite.vert", "./Shaders/Sprite.frag");
    if (!sprite_shader)
    {
        return false;
    }

    sprite_shader->Activate();

    const mat4 viewProj = math::SimpleViewProjection((f32) window::Width(), (f32) window::Height());
    sprite_shader->SetMatrix("ViewProj", viewProj);

    return true;
}

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

    if (!LoadShaders())
    {
        LOG_ERROR("Failed to load shaders");
        return false;
    }
    CreateSpriteVerts();

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

    core::UnloadTextures();
    core::UnloadShaders();

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
    glClearColor(0.85f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sprite_shader->Activate();
    sprite_verts->Activate();

    for (const auto sprite : m_sprites)
    {
        sprite->Draw(sprite_shader);
    }

    window::SwapBuffers();
}

} // namespace retract