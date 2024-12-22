#include "editor.hpp"
#include "Vendors/ImGui/imgui_internal.h"

namespace Debug {

    Editor::Editor() {
        this->widgets.emplace_back(&widgetConsole);
        this->widgets.emplace_back(&widgetActions);
        this->widgets.emplace_back(&widgetContentBrowser);
        this->widgets.emplace_back(&widgetInspector);
        this->widgets.emplace_back(&widgetGameView);
        this->widgets.emplace_back(&widgetSceneView);
        this->widgets.emplace_back(&widgetWorldHierarchy);
    };

    void Editor::ResetLayout(ImGuiID dockspace) {

        if (!ImGui::DockBuilderGetNode(dockspace)){

            ImGui::DockBuilderRemoveNode(dockspace); // Clear out existing layout
            ImGui::DockBuilderAddNode(dockspace); // Add empty node
            ImGui::DockBuilderSetNodeSize(dockspace, ImGui::GetIO().DisplaySize);

            ImGuiID mainDockspaceID = dockspace;
            
            this->layoutHeader        = ImGui::DockBuilderSplitNode(mainDockspaceID, ImGuiDir_Up,    0.045f, nullptr, &mainDockspaceID);
            this->layoutSceneViewport = ImGui::DockBuilderSplitNode(mainDockspaceID, ImGuiDir_Left,  0.8f, nullptr, &mainDockspaceID);
            this->layoutContent       = ImGui::DockBuilderSplitNode(mainDockspaceID, ImGuiDir_Right, 0.2f, nullptr, &mainDockspaceID);
            this->layoutFooter        = ImGui::DockBuilderSplitNode(layoutSceneViewport, ImGuiDir_Down,  0.3f, nullptr, &layoutSceneViewport);

            ImGui::DockBuilderDockWindow("Action Bar",      this->layoutHeader);
            ImGui::DockBuilderDockWindow("Game View",       this->layoutSceneViewport);
            ImGui::DockBuilderDockWindow("Scene View",      this->layoutSceneViewport);
            ImGui::DockBuilderDockWindow("Inspector",       this->layoutContent);
            ImGui::DockBuilderDockWindow("World Hierarchy", this->layoutContent);
            ImGui::DockBuilderDockWindow("Content Browser", this->layoutFooter);
            ImGui::DockBuilderDockWindow("Console",         this->layoutFooter);
            
            ImGui::DockBuilderFinish(dockspace);

        };

    };

    void Editor::AddWidget(ImGuiWidget::WidgetBase* widget) {
        this->widgets.emplace_back(widget);
    };

    void Editor::Render() {

        for (auto widget : this->widgets)
            widget->Render();

    };

};