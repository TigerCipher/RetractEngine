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
//  File Name: Window.cpp
//  Date File Created: 08/22/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "Window.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace retract::window
{

namespace
{
SDL_Window*   window_handle{};
SDL_GLContext gl_context{};
u32           window_width{};
u32           window_height{};
} // anonymous namespace

bool Init(const char* title, u32 width, u32 height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_ERROR("Failed to initialize SDL. Error: {}", SDL_GetError());
        return false;
    }

    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Specify version 4.4
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    window_width  = width;
    window_height = height;
    window_handle = SDL_CreateWindow(title, 100, 100, (i32)width, (i32)height, SDL_WINDOW_OPENGL);

    if (!window_handle)
    {
        LOG_ERROR("Failed to create window. Error: {}", SDL_GetError());
        SDL_Quit();
        return false;
    }

    gl_context = SDL_GL_CreateContext(window_handle);

    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        LOG_ERROR("Failed to initialize glew");
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window_handle);
        SDL_Quit();
        return false;
    }

    glGetError();

    return true;
}

void Shutdown()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window_handle);
    SDL_Quit();
}

void SwapBuffers()
{
    SDL_GL_SwapWindow(window_handle);
}

SDL_Window* Handle()
{
    return window_handle;
}

u32 Width()
{
    return window_width;
}

u32 Height()
{
    return window_height;
}

} // namespace retract::window