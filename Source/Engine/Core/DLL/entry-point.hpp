#pragma once
#include "Engine/Core/DLL/delayload.hpp"
#include "Engine/Debug/profiling.hpp"
#define SDL_MAIN_HANDLED

extern Engine::Application* Engine::CreateApplication(); 

int main(int argc, char** argv) {

    PROFILE_FUNCTION();

    PRE_DEFINE_LIBRARY_PATH(L"./Binaries/");

    auto app = Engine::CreateApplication();

    app->Run();
    
    delete app;

    return 0;

};