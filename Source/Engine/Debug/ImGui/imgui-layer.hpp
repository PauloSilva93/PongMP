#pragma once
#include "Vendors/ImGui/imgui.h"
#include "Vendors/ImGui/imgui_impl_sdl3.h"
#include "Vendors/ImGui/imgui_impl_opengl3.h"
#include "Vendors/SDL3/SDL.h"
#include "Engine/Core/Layers/layers.hpp"
#include "Engine/Debug/ImGui/editor.hpp"

namespace Debug {

    class ImGuiLayer : public Core::Layer {

        public:
            ImGuiLayer();

            void Begin();
            void End();
            
            void BeginDockspace();
            void EndDockspace();
        
            void OnAttach() override;
            void OnDetach() override;
            void OnEvent(/* PUT EVENT PARAMETER HERE */) override;
            void OnImGuiRender() override;

        private:
            bool isFullscreen = false;
            ImGuiID dockspaceID = 0;
            bool dockspaceBegin = false;
            Editor editor;

            void SetupFonts();


    };

};