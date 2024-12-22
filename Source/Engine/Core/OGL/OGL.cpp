#include "OGL.hpp"
#include <cstdio>
#include "Vendors/GLAD/glad.h"
#include "Engine/Debug/Logger.hpp"
#include "Engine/Debug/profiling.hpp"

namespace OGL {

    void Render::CreateEverything(SDL_Window* win) {

        PROFILE_FUNCTION();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        this->DefineGLVersion();

        this->InitContext(win);

        this->InitGLAD();

        this->DefineVSYNC(EVSync::SYNCHRONIZED);

    };

    void Render::InitContext(SDL_Window* win) {

        PROFILE_FUNCTION();

        this->gl_context = SDL_GL_CreateContext(win);        
        SDL_GL_MakeCurrent(win, this->gl_context);

    };
    
    void Render::InitGLAD() {

        PROFILE_FUNCTION();

        DEBUG_CHECK(
            gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress),
            "OPENGL",
            "GLAD has been initialized",
            "GLAD error"
        );

    };

    void Render::DefineVSYNC(EVSync interval){
    
        SDL_GL_SetSwapInterval(
            static_cast<int>(interval)
        );
    
    };

    void Render::DefineGLVersion(int minor, int major){

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, major);

    };

    void Render::DefineViewport(int x, int y, int w, int h) {

        glViewport(x, y, w, h);

    };

};