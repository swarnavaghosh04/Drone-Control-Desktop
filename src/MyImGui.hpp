#ifndef MYIMGUI__H
#define MYIMGUI__H

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "MySDL.hpp"

struct MyImGui{
    MyImGui() noexcept;
    ~MyImGui() noexcept;

    struct Backend{
        Backend(MySDL& sdl) noexcept;
        ~Backend() noexcept;
        void newFrame() noexcept;
        void draw() noexcept;
    };
};

#endif