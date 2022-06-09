#ifndef MYSDL__H
#define MYSDL__H

#include <SDL2/SDL.h>

struct MySDL{
    SDL_Window* window;
    SDL_GLContext gl_context;
    const char* glsl_version;

    MySDL() noexcept;
    ~MySDL() noexcept;
};

const char* setup_SDL_Attributes() noexcept;

#endif
