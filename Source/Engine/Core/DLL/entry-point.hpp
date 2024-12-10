#pragma once
#include "Engine/Debug/profiling.hpp"
#define SDL_MAIN_HANDLED

extern Engine::Application* Engine::CreateApplication(); 

int main(int argc, char** argv) {

    PROFILE_FUNCTION();

    auto app = Engine::CreateApplication();

    app->Run();
    
    delete app;

    return 0;

};