#pragma once
#include <string>
#include "Vendors/SDL3/SDL.h"

namespace OGL {

    enum class EVSync: int {

        ADAPTATIVE = -1,
        IMMEDIATE = 0,
        SYNCHRONIZED = 1,

    };

    class Render {

        public:
            Render() = default;
            ~Render() = default;

            void CreateEverything(SDL_Window* win);

            void DefineGLVersion(int minor = 3, int major = 3);
            void DefineVSYNC(EVSync interval);
            void DefineViewport(int x, int y, int w, int h);
            
            SDL_GLContext& GetGLContext() { return this->gl_context; };
            std::string GetGLSLVersion() const { return this->GLSLVersion; };

        private:
            SDL_GLContext gl_context;
            std::string GLSLVersion = "#version 330";

            void InitContext(SDL_Window* win);
            void InitGLAD();
    };

};