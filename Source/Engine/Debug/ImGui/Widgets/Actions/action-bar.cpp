#include "action-bar.hpp"
#include "Vendors/IconFont/IconsFontAwesome4.h"
#include "Vendors/ImGui/imgui.h"

namespace ImGuiWidget {

    void ActionBar::Render() {

        this->MenuBar();
        this->Actions();

    };

    void ActionBar::MenuBar() {

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New File")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Package"))
            {
                if (ImGui::MenuItem("Build PAK")) {}
                if (ImGui::MenuItem("Extract PAK")) {}
                if (ImGui::MenuItem("Read Files on PAK")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    };

    void ActionBar::Actions() {

        ImGuiWindowClass winclass;
        winclass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar |
                                            ImGuiDockNodeFlags_NoUndocking;
        ImGui::SetNextWindowClass(&winclass);

        ImGui::Begin("Action Bar");

            ImGui::Button(ICON_FA_ARROWS, ImVec2(32.0f, 32.0f));
            ImGui::SameLine();

            ImGui::Button(ICON_FA_REFRESH, ImVec2(32.0f, 32.0f)); 
            ImGui::SameLine();
            

        ImGui::End();

    };

};
