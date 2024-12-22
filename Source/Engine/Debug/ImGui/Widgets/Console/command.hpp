#pragma once
#include <string>
#include <vector>

class ConsoleCommand {

    public:
        virtual ~ConsoleCommand() = default;
        virtual void Execute(std::vector<std::string> args) = 0;

};