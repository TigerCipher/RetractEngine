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
//  File Name: Renderer.cpp
//  Date File Created: 08/25/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "Renderer.h"


#include "VertexArray.h"
#include "Retract/Core/Resources.h"
#include "Retract/Core/Window.h"

namespace retract::graphics
{

namespace
{
std::vector<Sprite*>        sprites{};
std::vector<MeshComponent*> meshes{};

Shader*      sprite_shader{};
Shader*      mesh_shader{};
VertexArray* sprite_verts{};

mat4 view{};
mat4 projection{};

vec3             ambient_light{};
DirectionalLight directional_light{};

void CreateSpriteVerts()
{
    const std::vector<f32> vertices{
        -0.5f, 0.5f,  0.f, 0.f, 0.f, 0.f, 0.f, 0.f, // top left
        0.5f,  0.5f,  0.f, 0.f, 0.f, 0.f, 1.f, 0.f, // top right
        0.5f,  -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f  // bottom left
    };

    const std::vector<u32> indices{ 0, 1, 2, 2, 3, 0 };

    sprite_verts = DBG_NEW VertexArray(vertices, 4, indices);
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

    mesh_shader = core::LoadShader("Mesh", "./Shaders/Phong.vert", "./Shaders/Phong.frag");
    if (!mesh_shader)
    {
        return false;
    }
    mesh_shader->Activate();
    view       = math::LookAt(math::zero_vec3, math::unitx_vec3, math::unitz_vec3);
    projection = math::Perspective(math::ToRadians(70.f), (f32) window::Width(), (f32) window::Height(), 25.f, 10000.f);
    mesh_shader->SetMatrix("ViewProj", view * projection);

    return true;
}

void SetLightUniforms(const Shader* shader)
{
    mat4 invView = view;
    invView.Invert();

    shader->SetVector("CameraPos", invView.Translation());
    shader->SetVector("AmbientLight", ambient_light);

    shader->SetVector("DirLight.direction", directional_light.direction);
    shader->SetVector("DirLight.diffuseColor", directional_light.diffuseColor);
    shader->SetVector("DirLight.specularColor", directional_light.specularColor);
}

} // anonymous namespace

bool Initialize()
{
    if (!LoadShaders())
    {
        LOG_ERROR("Failed to load shaders");
        return false;
    }
    CreateSpriteVerts();

    return true;
}

void Shutdown()
{
    delete sprite_verts;
    core::UnloadTextures();
    core::UnloadShaders();
    core::UnloadMeshes();
}

void AddSprite(Sprite* sprite)
{
    const i32 drawOrder = sprite->DrawOrder();
    auto      it        = sprites.begin();
    while (it != sprites.end())
    {
        if (drawOrder < (*it)->DrawOrder())
            break;
        ++it;
    }

    sprites.insert(it, sprite);
}

void RemoveSprite(Sprite* sprite)
{
    const auto it = std::ranges::find(sprites, sprite);
    sprites.erase(it);
}

void AddMesh(MeshComponent* mesh)
{
    meshes.emplace_back(mesh);
}

void RemoveMesh(MeshComponent* mesh)
{
    const auto it = std::ranges::find(meshes, mesh);
    meshes.erase(it);
}

void SetViewMatrix(const mat4& _view)
{
    view = _view;
}

void SetAmbientLight(const vec3& ambient)
{
    ambient_light = ambient;
}

DirectionalLight& GetDirectionalLight()
{
    return directional_light;
}


void Render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    mesh_shader->Activate();
    mesh_shader->SetMatrix("ViewProj", view * projection);
    SetLightUniforms(mesh_shader);

    for (const auto mc : meshes)
    {
        mc->Draw(mesh_shader);
    }

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    sprite_shader->Activate();
    sprite_verts->Activate();
    for (const auto sprite : sprites)
    {
        sprite->Draw(sprite_shader);
    }
}
void DrawIndexed(i32 count)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

f32 ScreenWidth()
{
    return (f32) window::Width();
}
f32 ScreenHeight()
{
    return (f32) window::Height();
}

} // namespace retract::graphics