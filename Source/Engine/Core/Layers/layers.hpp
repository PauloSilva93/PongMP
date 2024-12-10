#pragma once
#include <string>

namespace Core {

    class Layer {

        public:
            Layer(const std::string& name = "Default Layer Name");
            virtual ~Layer() = default;

            virtual void OnAttach() {};
            virtual void OnDetach() {};
            virtual void OnImGuiRender() {};
            virtual void OnUpdate() {};
            virtual void OnEvent(/* PUT EVENT PARAMETER HERE */) {};
        
            inline const std::string& GetName() const { return this->debugName; };

        private:
            std::string debugName;

    };

};
