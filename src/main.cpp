#define SDL_MAIN_HANDLED

#include <iostream>

#include "imgui.h"
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif
#include <libserialport.h>

#include "MySDL.hpp"
#include "MyImGui.hpp"

int libserialport_test(){

    struct sp_port **port_list;
    enum sp_return result = sp_list_ports(&port_list);

    if (result != SP_OK) {
		printf("sp_list_ports() failed!\n");
		return -1;
	}

    int i;
	for (i = 0; port_list[i] != NULL; i++) {
		struct sp_port *port = port_list[i];

		/* Get the name of the port. */
		char *port_name = sp_get_port_name(port);

		printf("Found port: %s\n", port_name);
	}

	printf("Found %d ports.\n", i);

    sp_free_port_list(port_list);

    return 0;

}

int main(){

    int errVal = libserialport_test();
    if(errVal != 0) return errVal;

    MySDL mySDL = MySDL();
    MyImGui myImGui = MyImGui();
    MyImGui::Backend backend = MyImGui::Backend(mySDL);

    ImGuiIO& io = ImGui::GetIO();

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    float rotors[] = {0.f, 0, 0, 0};

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

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(50,50));

            ImGui::BeginGroup();
            ImGui::Text("Hello");
            ImGui::Text("bye");
            ImGui::EndGroup();

            ImGui::SameLine();

            ImGui::VSliderFloat("Rotor 1", ImVec2(30,400), &rotors[0], 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 2", ImVec2(30,400), &rotors[1], 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 3", ImVec2(30,400), &rotors[2], 0.f, 1.f, "");
            ImGui::SameLine();
            ImGui::VSliderFloat("Rotor 4", ImVec2(30,400), &rotors[3], 0.f, 1.f, "");

            ImGui::PopStyleVar();

            ImGui::End();
        }

        // Uncomment to see ImGui help window
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(mySDL.window);
    }

    // Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplSDL2_Shutdown();

    return 0;
}