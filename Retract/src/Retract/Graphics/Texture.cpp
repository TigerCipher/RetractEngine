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
//  File Name: Texture.cpp
//  Date File Created: 08/24/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Texture.h"

#include <GL/glew.h>
#include <SOIL2/SOIL2.h>

namespace retract
{

Texture::Texture(const std::string& filename)
{
    Load(filename);
}
Texture::~Texture()
{
    LOG_WARN("Deleting texture");
}

bool Texture::Load(const std::string& filename)
{
    LOG_INFO("Loading texture {}", filename);
    i32 channels = 0;

    u8* image = SOIL_load_image(filename.c_str(), &mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);

    if (!image)
    {
        LOG_ERROR("Failed to load image '{}' - {}", filename, SOIL_last_result());
        return false;
    }

    i32 format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);

    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::Unload() const
{
    glDeleteTextures(1, &mId);
}

void Texture::Activate() const
{
    glBindTexture(GL_TEXTURE_2D, mId);
}

}