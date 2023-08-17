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
// File Name: Main
// Date File Created: 08/17/2023
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Retract/Core/Game.h"

#pragma comment(lib, "Retract.lib")

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#include "Retract/Components/Entity.h"
#include "Retract/Components/Sprite.h"


#include <Windows.h>
#include <crtdbg.h>


using namespace retract;


class Asteroid : public Entity
{
public:
    Asteroid(core::Game* game) : Entity{ game }
    {
        m_sprite = new Sprite(this);
        m_sprite->SetTexture(game->GetTexture("./Content/asteroid.png"));
        SetPosition({ 100, 100 });
    }
    ~Asteroid() override { delete m_sprite; }
    void UpdateEntity(f32 delta) override {}

private:
    Sprite* m_sprite;
};

class Sandbox : public core::Game
{
public:
    Sandbox() : Game() {}

    void Init() override
    {
        LOG_INFO("Sandbox game initialized");
        AddEntity(new Asteroid(this));
    }
};

//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    Sandbox game{};

    const i32 status = game.Run();

    return status;
}
