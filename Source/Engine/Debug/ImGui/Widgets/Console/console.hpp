#pragma once
#include <ctime>
#include <string>
#include <array>
#include <unordered_map>
#include "Vendors/ImGui/imgui.h"
#include "Engine/Debug/ImGui/Base/widget.hpp"
#include "Engine/Debug/Logger.hpp"

#include "Engine/Debug/ImGui/Widgets/Console/command.hpp"

#define COMMAND_HISTORY_ARRAY_SIZE 15

namespace ImGuiWidget {

    class Console : public WidgetBase {

        public:
            Console();
            ~Console() = default;

            virtual void Render() override;

            void RenderLogging();
            void RenderCommandLine();

        private:

            int commandHistoryIndex = 0;
            std::string commandBuffer;
            std::array<std::string, COMMAND_HISTORY_ARRAY_SIZE> commandHistory;
            std::unordered_map<std::string, ConsoleCommand*> commands;

            ImVec4 ColorFromLogLevel(Debug::ELogLevel level);
            const char* TextFromTime(std::time_t timestamp);
            static int CommandLineCallback(ImGuiInputTextCallbackData* data);
            void ExecuteCommand();


    };

    
    

};