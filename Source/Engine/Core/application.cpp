#include "application.hpp"
#include "Vendors/GLAD/glad.h"
#include "Vendors/SDL3/SDL_net.h"
#include "Engine/Debug/logger.hpp"
#include "Engine/Debug/profiling.hpp"

namespace Engine {

    Application* Application::instance = nullptr;

    Application::Application() {

        PROFILE_FUNCTION();

        this->instance = this;

        DEBUG_CHECK(
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS), 
            "APPLICATION", 
            "SDL Started",
            "SDL Error: %s", SDL_GetError()
        );

        this->window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        DEBUG_CHECK(
            (this->window != nullptr),
            "APPLICATION", 
            "SDL Window Has been Initialized",
            "SDL Window pointer is null"
        );

        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_MaximizeWindow(window);

        this->renderer.CreateEverything(window);

        SDL_ShowWindow(window);

        imGuiLayer = new Debug::ImGuiLayer();
        PushOverlay(imGuiLayer);

        this->isRunning = true;

        DEBUG_LOG("APPLICATION", "Testando Aqui");
        DEBUG_VERBOSE("APPLICATION", "Testando Aqui");
        DEBUG_SUCCESS("APPLICATION", "Testando Aqui");
        DEBUG_WARNING("APPLICATION", "Testando Aqui");
        DEBUG_ERROR("APPLICATION", "Testando Aqui");

        DEBUG_CHECK(true, "APPLICATION", "Condition Initialized %d", "Condition Error %d", 1234);
        DEBUG_CHECK(false, "APPLICATION", "Condition Initialized %d", "Condition Error %d", 1234);

    };

    Application::~Application() {

        PROFILE_FUNCTION();

        SDL_DestroyWindow(this->window);
        SDL_Quit();

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