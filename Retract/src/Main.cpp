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

#include <iostream>

#include "Retract/Core/Game.h"

using namespace retract;

int main(int argc, char* argv[])
{
    core::Game game{};
    if(!game.Initialize())
    {
        std::cerr << "Something went wrong\n";
        return -1;
    }

    game.Run();
    game.Shutdown();

    return 0;
}
