#pragma once
#include "Vendors/SDL3/SDL.h"
#include "Engine/Core/Layers/layers.hpp"
#include "Engine/Core/Layers/layer-stack.hpp"
#include "Engine/Debug/ImGui/imgui-layer.hpp"
#include "Engine/Core/OGL/OGL.hpp"

namespace Engine {

    class Application {

        public:

            Application();
            virtual ~Application();

            void PushLayer(Core::Layer* layer);
            void PushOverlay(Core::Layer* layer);

            void Run();

            void OnEvent();
            void OnUpdate();
            void OnImGuiRender();
            void OnRender();

            static Application& Get() { return *instance; };
            SDL_Window& GetWindow() { return *this->window; };
            OGL::Render& GetRenderer() { return this->renderer; };

        private:
            static Application* instance;

            bool isRunning = false;
            Core::LayerStack layerStack;
            
            SDL_Window* window = nullptr;
            SDL_Event event;

            OGL::Render renderer;

            Debug::ImGuiLayer* imGuiLayer = nullptr;

    };

    // To be define in client;
    Application* CreateApplication();

};