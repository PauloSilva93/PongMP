#include "console.hpp"
#include <string>
#include <vector>
#include <cstdarg>
#include <cstdint>
#include "Vendors/glm/glm.hpp"
#include "Vendors/ImGui/imgui_stdlib.h"
#include "Engine/Debug/ImGui/Widgets/Console/Commands/helper.hpp"
#include "Engine/Helpers/string.hpp"

namespace ImGuiWidget {

    Console::Console() {

        commands["Help"] = new ConsoleHelperCommand();

    };

    void Console::Render() {

        ImGui::SetNextWindowSize(ImVec2(1280.0f, 300.0f));
        ImGui::Begin("Console");

            this->RenderLogging();
            this->RenderCommandLine();            

        ImGui::End();

    };

    void Console::RenderLogging() {

        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | 
                                       ImGuiTableFlags_Borders | 
                                       ImGuiTableFlags_Reorderable | 
                                       ImGuiTableFlags_Hideable | 
                                       ImGuiTableFlags_PreciseWidths |
                                       ImGuiTableFlags_NoHostExtendX |
                                       ImGuiTableFlags_SizingFixedSame |
                                       ImGuiTableFlags_ScrollY;

        if (ImGui::BeginTable("table1", 4, flags, ImVec2(1280.0f, 250.0f))) {

            ImGui::TableSetupColumn("Timestamp",    ImGuiTableColumnFlags_WidthFixed, 180.0f);
            ImGui::TableSetupColumn("Status | Tag", ImGuiTableColumnFlags_WidthFixed, 250.0f);
            ImGui::TableSetupColumn("Message",      ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("File:Line",    ImGuiTableColumnFlags_WidthFixed, 160.0f);
                
            ImGui::TableHeadersRow();
                
            for (auto it = Debug::Logger::messages.begin(); it != Debug::Logger::messages.end(); it++) {

                Debug::LogMessage msg = *it;

                ImVec4 color = this->ColorFromLogLevel(msg.level);
                // const char* textTime = this->TextFromTime(msg.timestamp);

                char textTime[96];
                std::tm timePtr;
                localtime_s(&timePtr, &msg.timestamp);
                std::strftime(textTime, sizeof(textTime), "%Y-%m-%d  %H:%M:%S", &timePtr);

                ImGui::TableNextRow();
                for (int column = 0; column < 4; column++) {

                    ImGui::TableSetColumnIndex(column);
                         if (column == 0) ImGui::TextColored(color, "%s", textTime);
                    else if (column == 1) ImGui::TextColored(color, "%s\t|%s", msg.levelText, msg.tag);
                    else if (column == 2) ImGui::TextColored(color, "%s", msg.message);
                    else if (column == 3) ImGui::TextColored(color, "%s:%d", msg.file, msg.lineNumber);
                
                };

            };
        
            ImGui::EndTable();
        
        };

    };

    void Console::RenderCommandLine() {

        ImGuiInputTextFlags commandInputFlags = ImGuiInputTextFlags_EnterReturnsTrue | 
                                                ImGuiInputTextFlags_EscapeClearsAll | 
                                                ImGuiInputTextFlags_CallbackCompletion | 
                                                ImGuiInputTextFlags_CallbackHistory;

        if (ImGui::InputText("Input", &commandBuffer, commandInputFlags, Console::CommandLineCallback, (void*)this))
            this->ExecuteCommand();

    };

    int Console::CommandLineCallback(ImGuiInputTextCallbackData* data) {

        DEBUG_LOG("CONSOLE", "Teste");

        return 0;
    };
    
    ImVec4 Console::ColorFromLogLevel(Debug::ELogLevel level) {

        ImVec4 color;

        switch(level){
            case Debug::ELogLevel::DEBUG:   color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); break;
            case Debug::ELogLevel::VERBOSE: color = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); break;
            case Debug::ELogLevel::SUCCESS: color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); break;
            case Debug::ELogLevel::WARNING: color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); break;
            case Debug::ELogLevel::ERROR:   color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); break;
            case Debug::ELogLevel::ASSERT:  color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); break;

            default: color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); break;
        
        };

        return color;

    };

    const char* Console::TextFromTime(std::time_t timestamp) {

        char textTime[96];
        std::tm timePtr;
        localtime_s(&timePtr, &timestamp);
        std::strftime(textTime, sizeof(textTime), "%Y-%m-%d  %H:%M:%S", &timePtr);

        return textTime;

    };

    void Console::ExecuteCommand() {

        // Print Text Command on Console
        DEBUG_VERBOSE("COMMAND", "%s", commandBuffer.c_str());
        commandHistory[commandHistoryIndex] = commandBuffer;
        commandHistoryIndex++;

        if (commandHistoryIndex > COMMAND_HISTORY_ARRAY_SIZE) 
            commandHistoryIndex = 0;
        else if (commandHistoryIndex < 0) 
            commandHistoryIndex = COMMAND_HISTORY_ARRAY_SIZE - 1;
        
        // Split Command Array
        auto command = Helpers::String::Split(commandBuffer, ' ');

        // If Command has on map
        if (commands.contains(command.at(0))) {
            
            ConsoleCommand* consoleCommand = commands.at(command.at(0));

            command.erase(command.begin());     // Remove Command Remaining Only Args
            consoleCommand->Execute(command);   // Execute Command
        
        };

        // Clear Buffer
        commandBuffer.clear();

    };

};