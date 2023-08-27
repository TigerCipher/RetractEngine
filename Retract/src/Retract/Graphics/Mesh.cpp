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
//  File Name: Mesh.cpp
//  Date File Created: 08/26/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Mesh.h"
#include "Renderer.h"
#include "Retract/Core/Resources.h"


#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

namespace retract
{

bool Mesh::Load(const std::string& filename)
{
    LOG_INFO("Loading mesh {}", filename);
    std::ifstream file{ filename };
    if (!file.is_open())
    {
        LOG_WARN("Mesh file not found: {}", filename);
        return false;
    }

    std::stringstream filestream{};
    filestream << file.rdbuf();
    std::string             contents = filestream.str();
    rapidjson::StringStream jsonStr{ contents.c_str() };
    rapidjson::Document     doc{};
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        LOG_WARN("Mesh '{}' is not a valid json object", filename);
        return false;
    }

    i32 ver = doc["version"].GetInt();
    if (ver != 1)
    {
        LOG_WARN("Mesh '{}' is not version 1", filename);
        return false;
    }

    mShaderName = doc["shader"].GetString();

    const rapidjson::Value& textures = doc["textures"];
    if (!textures.IsArray() || textures.Size() < 1)
    {
        LOG_WARN("Mesh '{}' has no textures. There should be at least one", filename);
        return false;
    }

    mSpecularPower = (f32) doc["specularPower"].GetDouble();

    for (rapidjson::SizeType i = 0; i < textures.Size(); ++i)
    {
        std::string textureName = textures[i].GetString();
        Texture*    t           = core::GetTexture(textureName);
        if (!t)
        {
            t = core::GetTexture("./Content/default.png");
        }
        mTextures.emplace_back(t);
    }

    constexpr u64 vertSize = 8;

    const rapidjson::Value& vertsJson = doc["vertices"];
    if (!vertsJson.IsArray() || vertsJson.Size() < 1)
    {
        LOG_WARN("Mesh '{}' has no vertices", filename);
        return false;
    }

    std::vector<f32> verts{};
    verts.reserve(vertsJson.Size() * vertSize);
    mRadius = 0.f;
    for (rapidjson::SizeType i = 0; i < vertsJson.Size(); ++i)
    {
        const rapidjson::Value& vert = vertsJson[i];
        if (!vert.IsArray() || vert.Size() != vertSize)
        {
            LOG_WARN("Unexptected vertex format in mesh '{}'", filename);
            return false;
        }

        vec3 pos{ (f32) vert[0].GetDouble(), (f32) vert[1].GetDouble(), (f32) vert[2].GetDouble() };
        mRadius = math::Max(mRadius, pos.LengthSq());

        for (rapidjson::SizeType j = 0; j < vert.Size(); ++j)
        {
            verts.emplace_back((f32) vert[j].GetDouble());
        }
    }

    mRadius = math::Sqrt(mRadius);

    const rapidjson::Value& indJson = doc["indices"];
    if (!indJson.IsArray() || indJson.Size() < 1)
    {
        LOG_WARN("Mesh '{}' has no indices", filename);
        return false;
    }

    std::vector<u32> indices{};
    indices.reserve(indJson.Size() * 3);

    for (rapidjson::SizeType i = 0; i < indJson.Size(); ++i)
    {
        const rapidjson::Value& ind = indJson[i];
        if (!ind.IsArray() || ind.Size() != 3)
        {
            LOG_WARN("Invalid indices format for mesh '{}'", filename);
            return false;
        }

        indices.emplace_back(ind[0].GetUint());
        indices.emplace_back(ind[1].GetUint());
        indices.emplace_back(ind[2].GetUint());
    }

    mVertexArray = DBG_NEW VertexArray{ verts, (u32)verts.size() / (u32)vertSize, indices };
    LOG_INFO("Mesh '{}' loaded", filename);
    return true;
}

void Mesh::Unload()
{
    SAFE_DELETE(mVertexArray);
}

Texture* Mesh::GetTexture(u32 index) const
{
    if (index < mTextures.size())
    {
        return mTextures[index];
    }

    return nullptr;
}

} // namespace retract