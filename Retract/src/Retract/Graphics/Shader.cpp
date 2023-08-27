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
//  File Name: Shader.cpp
//  Date File Created: 08/24/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Shader.h"


#include <fstream>
#include <sstream>

namespace retract
{

namespace
{
bool IsCompiled(GLuint shader)
{
    GLint status{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        LOG_ERROR("Shader compilation failure:\n{}", buffer);
        return false;
    }

    return true;
}

bool Compile(const std::string& filename, GLenum shader_type, GLuint& out_shader)
{
    if (const std::ifstream shaderFile{ filename }; shaderFile.is_open())
    {
        LOG_INFO("Compiling shader '{}'", filename);
        std::stringstream ss;
        ss << shaderFile.rdbuf();
        const std::string str      = ss.str();
        const char*       contents = str.c_str();

        out_shader = glCreateShader(shader_type);

        glShaderSource(out_shader, 1, &contents, nullptr);
        glCompileShader(out_shader);

        if (!IsCompiled(out_shader))
        {
            LOG_ERROR("Failed to compile shader '{}'", filename);
            return false;
        }
    } else
    {
        LOG_ERROR("Shader file '{}' not found", filename);
        return false;
    }

    return true;
}

} // anonymous namespace

Shader::Shader(const std::string& vertex, const std::string& frag)
{
    Load(vertex, frag);
}
Shader::~Shader()
{
    LOG_WARN("Deleting shader");
}

bool Shader::Load(const std::string& vertex, const std::string& frag)
{
    if (!Compile(vertex, GL_VERTEX_SHADER, mVertexShader) || !Compile(frag, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }

    mProgram = glCreateProgram();
    glAttachShader(mProgram, mVertexShader);
    glAttachShader(mProgram, mFragShader);
    glLinkProgram(mProgram);

    return IsValid();
}

void Shader::Unload() const
{
    glDeleteProgram(mProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::Activate() const
{
    glUseProgram(mProgram);
}

void Shader::SetMatrix(const char* name, const mat4& matrix) const
{
    const GLint loc = glGetUniformLocation(mProgram, name);
    assert(loc != -1);
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.data());
}

void Shader::SetVector(const char* name, const vec3& vec) const
{
    const GLint loc = glGetUniformLocation(mProgram, name);
    assert(loc != -1);
    glUniform3fv(loc, 1, vec.data());
}

void Shader::SetFloat(const char* name, f32 value) const
{
    const GLint loc = glGetUniformLocation(mProgram, name);
    assert(loc != -1);
    glUniform1f(loc, value);
}

bool Shader::IsValid() const
{
    GLint status{};
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512] = {};
        glGetProgramInfoLog(mProgram, 511, nullptr, buffer);
        LOG_ERROR("Shader link failure:\n{}", buffer);
        return false;
    }

    return true;
}
} // namespace retract