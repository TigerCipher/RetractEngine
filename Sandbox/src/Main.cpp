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
#include "Background.h"
#include "Ship.h"


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
    ~Asteroid() override
    {
        LOG_WARN("Deleting asteroid");
        delete m_sprite;
    }
    void UpdateEntity(f32 delta) override {}

private:
    Sprite* m_sprite;
};

class Sandbox : public core::Game
{
public:
    Sandbox() : Game() {  }

    ~Sandbox() override
    {
        //RemoveEntity(asteroid);
        delete asteroid;
        delete temp;
        delete ship;
    }

    void Init() override
    {
        LOG_INFO("Sandbox game initialized");
        asteroid = new Asteroid(this);
        //AddEntity(asteroid);

        ship = new Ship(this);
        ship->SetPosition({100.f, 384.f});
        

        temp = new Entity(this);
        temp->SetPosition({ 512, 400 });
        Background* bg = new Background(temp);
        bg->SetScreenSize({ 1000, 800 });
        utl::vector<SDL_Texture*> bgtex{
            GetTexture("./Content/bg01.png"),
            GetTexture("./Content/bg02.png"),
        };
        bg->SetTextures(bgtex);
        bg->SetScrollSpeed(-100.f);

        bg = new Background(temp, 50);
        bg->SetScreenSize({ 1000, 800 });
        bgtex.clear();
        bgtex.emplace_back(GetTexture("./Content/stars.png"));
        bgtex.emplace_back(GetTexture("./Content/stars.png"));
        bg->SetTextures(bgtex);
        bg->SetScrollSpeed(-200.f);
    }
    void ProcessInput(const u8* key_state) override
    {
        ship->ProcessKeyboard(key_state);
    }

private:
    Asteroid* asteroid{ nullptr };
    Entity* temp{nullptr};
    Ship* ship{nullptr};
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
