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
//  File Name: Resources.cpp
//  Date File Created: 08/24/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Resources.h"


#include <ranges>

namespace retract::core
{

namespace
{
std::unordered_map<std::string, Texture*> textures{};
std::unordered_map<std::string, Shader*>  shaders{};
std::unordered_map<std::string, Mesh*>    meshes{};
} // anonymous namespace

Texture* GetTexture(const std::string& filename)
{
    if (const auto it = textures.find(filename); it != textures.end())
    {
        return it->second;
    }

    if (auto tex = DBG_NEW Texture{}; tex->Load(filename))
    {
        textures.emplace(filename, tex);
        return tex;
    }

    return nullptr;
}

void UnloadTextures()
{
    for (const auto& tex : textures | std::views::values)
    {
        tex->Unload();
        delete tex;
    }
}

Shader* LoadShader(const std::string& name, const std::string& vertex, const std::string& frag)
{
    if (auto shader = DBG_NEW Shader{}; shader->Load(vertex, frag))
    {
        shaders.emplace(name, shader);
        return shader;
    }

    return nullptr;
}

Shader* GetShader(const std::string& name)
{
    assert(shaders.contains(name));
    return shaders[name];
}
void UnloadShaders()
{
    for (const auto& s : shaders | std::views::values)
    {
        s->Unload();
        delete s;
    }
}

Mesh* GetMesh(const std::string& filename)
{
    Mesh* m{};
    if (const auto it = meshes.find(filename); it != meshes.end())
    {
        m = it->second;
    } else
    {
        m = DBG_NEW Mesh{};
        if (m->Load(filename))
        {
            meshes.emplace(filename, m);
        } else
        {
            SAFE_DELETE(m);
        }
    }

    return m;
}

void UnloadMeshes()
{
    for (const auto& m : meshes | std::views::values)
    {
        m->Unload();
        delete m;
    }
}

} // namespace retract::core