#define SDL_MAIN_HANDLED

#include <iostream>

#include "imgui.h"
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#include "MySDL.hpp"
#include "MyImGui.hpp"
#include "MySerialPorts.hpp"
#include "Rotors.hpp"

int main(){

    MySDL mySDL = MySDL();
    MyImGui myImGui = MyImGui();
    MyImGui::Backend backend = MyImGui::Backend(mySDL);

    ImGuiIO& io = ImGui::GetIO();

    // Our state
    // bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    Rotors rotors = Rotors();
    MySerialPorts sp;

    // Main loop
    bool done = false;
    while (!done)
    {
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(mySDL.window))
                done = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
        }

        // Start the Dear ImGui frame
        backend.newFrame();
        ImGui::NewFrame();

        {
            const ImGuiViewport* vp = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(vp->WorkPos);
            ImGui::SetNextWindowSize(vp->WorkSize);

            const auto flags =
                ImGuiWindowFlags_NoResize       |
                ImGuiWindowFlags_NoMove         |
                ImGuiWindowFlags_NoCollapse     |
                ImGuiWindowFlags_NoDecoration   |
                ImGuiWindowFlags_NoBackground;

            ImGui::Begin("Controls", NULL, flags);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(50,10));

            ImGui::BeginGroup();
            ImGui::Text("Select Arduino Serial Port:");
            ImGui::BeginChild("Arduino Selector", ImVec2(150, 300), true);
            for(int i = 0; sp.port_list[i] != NULL; i++){
                sp_port* port = sp.port_list[i];
                ImGui::RadioButton(sp_get_port_name(port), &sp.chosen_port, i);
            }
            ImGui::EndChild();
            if(ImGui::Button("Refersh list")) sp.refresh_port_list();
            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::VSliderFloat("Rotor 1", ImVec2(30,400), &rotors.r1, 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 2", ImVec2(30,400), &rotors.r2, 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 3", ImVec2(30,400), &rotors.r3, 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 4", ImVec2(30,400), &rotors.r4, 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Master", ImVec2(30,400), &rotors.master, 0.f, 1.f, "");

            ImGui::PopStyleVar();

            ImGui::End();
        }

        // Uncomment to see ImGui help window
        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        backend.draw();

        SDL_GL_SwapWindow(mySDL.window);

        rotors.process();
        sp.send_data(rotors);
    }

    return 0;
}