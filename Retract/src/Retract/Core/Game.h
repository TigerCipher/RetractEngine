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

#include <SDL.h>


namespace retract
{
class Entity;
class Sprite;

class Game
{
public:
    Game()          = default;
    virtual ~Game() = default;

    i32  Run(); // returns 0 if no issues

    virtual void Init() = 0;
    virtual void ProcessInput(const u8* key_state) {}

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

    void AddSprite(Sprite* sprite);
    void RemoveSprite(Sprite* sprite);

    SDL_Texture* GetTexture(const char* filename); // TODO: Add to a resource manager instead

    template<typename T>
    T* As()
    {
        return dynamic_cast<T*>(this);
    }

private:
    bool InitializeInternal();
    void ShutdownInternal();
    void ProcessInputInternal();
    void Update();
    void Render();
    SDL_Texture* LoadTexture(const char* filename);

    bool          m_running{ false };
    SDL_Window*   m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr }; // TODO: Testing purposes only

    utl::vector<Entity*> m_entities{};
    utl::vector<Entity*> m_pending_entities{};
    bool                 m_updating_entities{ false };

    std::unordered_map<std::string, SDL_Texture*> m_textures{};
    utl::vector<Sprite*> m_sprites{};
};

} // namespace retract::core
