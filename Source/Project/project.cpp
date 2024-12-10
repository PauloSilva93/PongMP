#include "Engine.hpp"

class ProjectApp : public Engine::Application {

    public:
        ProjectApp() {
            
        };
        ~ProjectApp() {
            
        };    

};

Engine::Application* Engine::CreateApplication() {

    return new ProjectApp();

};