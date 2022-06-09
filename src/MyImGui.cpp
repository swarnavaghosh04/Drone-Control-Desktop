#include "MyImGui.hpp"

MyImGui::MyImGui() noexcept{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
}

MyImGui::~MyImGui() noexcept{
    ImGui::DestroyContext();
}

MyImGui::Backend::Backend(MySDL& sdl) noexcept{
    ImGui_ImplSDL2_InitForOpenGL(sdl.window, sdl.gl_context);
    ImGui_ImplOpenGL3_Init(sdl.glsl_version);
}

MyImGui::Backend::~Backend() noexcept{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
}

void MyImGui::Backend::newFrame() noexcept{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
}