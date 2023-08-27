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

#pragma comment(lib, "Retract.lib")

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#include "Asteroids/Sandbox.h"

#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>


using namespace retract;




//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(378); // SDL_INIT_AUDIO seems to lead to the memory leak
#endif
    Sandbox game{};
    //TowerGame game{};

    const i32 status = game.Run();

    return status;
}
