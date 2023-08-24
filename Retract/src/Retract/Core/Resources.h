//  ------------------------------------------------------------------------------
//
//  RetractEngine
//     Copyright 2023 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  File Name: Resources.h
//  Date File Created: 08/24/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Retract/Common.h"
#include "Retract/Graphics/Shader.h"
#include "Retract/Graphics/Texture.h"

namespace retract::core
{

ref<Texture> GetTexture(const std::string& filename);
void UnloadTextures();

ref<Shader> LoadShader(const std::string& name, const std::string& vertex, const std::string& frag);
ref<Shader> GetShader(const std::string& name);
void UnloadShaders();

}