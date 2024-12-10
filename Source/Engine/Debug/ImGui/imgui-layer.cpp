#include "imgui-layer.hpp"
#include "Engine/Core/application.hpp"
#include "Engine/Core/OGL/OGL.hpp"
#include "Engine/Debug/profiling.hpp"

namespace Debug {

    ImGuiLayer::ImGuiLayer() : Core::Layer("ImGui Layer") {

        PROFILE_FUNCTION();

    };

    void ImGuiLayer::OnAttach() {

        PROFILE_FUNCTION();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        Engine::Application& app = Engine::Application::Get(); 
        SDL_Window* window = &app.GetWindow();
        OGL::Render renderer = app.GetRenderer();

        ImGui_ImplOpenGL3_Init(renderer.GetGLSLVersion().c_str());
        ImGui_ImplSDL3_InitForOpenGL(window, renderer.GetGLContext());

    };

    void ImGuiLayer::OnDetach() {

        PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

    };

    void ImGuiLayer::OnEvent(/* PUT EVENT PARAMETER HERE */) {

        PROFILE_FUNCTION();

    };

    void ImGuiLayer::OnImGuiRender() {

        PROFILE_FUNCTION();

        ImGui::ShowDemoWindow();

    };

    void ImGuiLayer::Begin() {

        PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

    };

    void ImGuiLayer::End() {

        PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

    };


};