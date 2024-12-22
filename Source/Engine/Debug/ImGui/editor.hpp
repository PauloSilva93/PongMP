#pragma once
#include <vector>
#include "Vendors/ImGui/imgui.h"
#include "Base/widget.hpp"
#include "Engine/Debug/ImGui/Widgets/Console/console.hpp"
#include "Engine/Debug/ImGui/Widgets/Actions/action-bar.hpp"
#include "Engine/Debug/ImGui/Widgets/ContentBrowser/content-browser.hpp"
#include "Engine/Debug/ImGui/Widgets/Inspector/inspector.hpp"
#include "Engine/Debug/ImGui/Widgets/SceneViewport/scene-view.hpp"
#include "Engine/Debug/ImGui/Widgets/SceneViewport/game-view.hpp"
#include "Engine/Debug/ImGui/Widgets/WorldHierarchy/world-hierarchy.hpp"

namespace Debug {

    class Editor {

        public:
            Editor();
            virtual ~Editor() = default;
            // void Layout();

            void ResetLayout(ImGuiID dockspace);
            void AddWidget(ImGuiWidget::WidgetBase* widget);

            void Render();

        private:
            ImGuiID layoutHeader;
            ImGuiID layoutSceneViewport;
            ImGuiID layoutContent;
            ImGuiID layoutFooter;

            std::vector<ImGuiWidget::WidgetBase*> widgets;
            ImGuiWidget::Console widgetConsole;
            ImGuiWidget::ActionBar widgetActions;
            ImGuiWidget::ContentBrowser widgetContentBrowser;
            ImGuiWidget::Inspector widgetInspector;
            ImGuiWidget::GameView widgetGameView;
            ImGuiWidget::SceneView widgetSceneView;
            ImGuiWidget::WorldHierarchy widgetWorldHierarchy;

    };

};