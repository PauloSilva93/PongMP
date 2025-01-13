#include "package-viewer.hpp"
#include "Vendors/ImGui/imgui.h"

namespace ImGuiWidget {

    void PackageViewer::Render() {

        ImGui::Begin("Package Viewer");

            ImGui::InputText("", nullptr, 200); ImGui::SameLine();
            ImGui::Button("Load");
            
            ImGui::Separator();

            static int selected = 0;
            ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
            for (int i = 0; i < 100; i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                // char label[128];
                // sprintf(label, "MyObject %d", i);
                // if (ImGui::Selectable(label, selected == i))
                //     selected = i;
            };
            ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        ImGui::EndChild();
        ImGui::EndGroup();

        ImGui::End();

    };



};