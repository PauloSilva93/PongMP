#include "application.hpp"
#include "Vendors/GLAD/glad.h"
#include "Engine/Debug/profiling.hpp"

namespace Engine {

    Application* Application::instance = nullptr;

    Application::Application() {

        PROFILE_FUNCTION();

        this->instance = this;

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
            printf("Error: SDL_Init(): %s\n", SDL_GetError());        
        };

        this->window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (this->window == nullptr)
            printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());

        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        this->renderer.CreateEverything(window);

        SDL_ShowWindow(window);

        imGuiLayer = new Debug::ImGuiLayer();
        PushOverlay(imGuiLayer);

        this->isRunning = true;

    };

    Application::~Application() {

        PROFILE_FUNCTION();
    };

    
    void Application::Run() {

        PROFILE_FUNCTION();

        while(this->isRunning) {

            this->OnEvent();

            this->OnUpdate();
            
            this->OnRender();
            
            this->OnImGuiRender();

            SDL_GL_SwapWindow(window);

        };

    };

    void Application::OnEvent() {

        while (SDL_PollEvent(&event)) {

            PROFILE_FUNCTION();

            ImGui_ImplSDL3_ProcessEvent(&event);
            
            if (event.type == SDL_EVENT_QUIT)
                this->isRunning = false;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                this->isRunning = false;
                
        };

    };
    
    void Application::OnUpdate() {

        PROFILE_FUNCTION();

        for (Core::Layer* layer : this->layerStack)
            layer->OnUpdate();

    };

    void Application::OnImGuiRender() {

        PROFILE_FUNCTION();

        imGuiLayer->Begin();

            for (Core::Layer* layer : this->layerStack)
                layer->OnImGuiRender();
        
        imGuiLayer->End();

    };

    void Application::OnRender() {

        PROFILE_FUNCTION();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    };

    
    void Application::PushLayer(Core::Layer* layer) {

        PROFILE_FUNCTION();

        this->layerStack.PushLayer(layer);
        layer->OnAttach();

    };

    void Application::PushOverlay(Core::Layer* layer) {

        PROFILE_FUNCTION();

        this->layerStack.PushOverlay(layer);
        layer->OnAttach();

    };


};