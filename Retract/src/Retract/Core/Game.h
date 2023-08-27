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


namespace retract
{
class Entity;
class Sprite;

class Game
{
public:
    Game();
    virtual ~Game() = default;

    i32 Run(); // returns 0 if no issues

    virtual void Init() = 0;
    virtual void ProcessInput(const u8* key_state) {}

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

    template<typename T>
    static T* As()
    {
        return dynamic_cast<T*>(mInstance);
    }

    static Game* Instance() { return mInstance; }

private:
    bool InitializeInternal();
    void ShutdownInternal() const;
    void ProcessInputInternal();
    void Update();
    void Render() const;

    bool m_running{ false };

    utl::vector<Entity*> m_entities{};
    utl::vector<Entity*> m_pending_entities{};
    bool                 m_updating_entities{ false };

    static Game* mInstance;
    static bool  mConstructed;
};

} // namespace retract
