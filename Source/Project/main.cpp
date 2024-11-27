#include <iostream>
#include "Engine/Engine.hpp"

int main(int argc, char** argv) {

    std::cout << "Hello World" << std::endl;
    Engine* engine = new Engine();
    engine->Start();

    return 0;

};