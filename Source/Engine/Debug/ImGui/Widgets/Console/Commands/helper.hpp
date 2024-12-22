#pragma once
#include "Engine/Debug/ImGui/Widgets/Console/command.hpp"
#include "Engine/Debug/logger.hpp"

class ConsoleHelperCommand : public ConsoleCommand {

    public: 

        ~ConsoleHelperCommand() {};

        void Execute(std::vector<std::string> args) override {

            DEBUG_VERBOSE("HELPER", "Command: Help - Show All Commands");

        };

};