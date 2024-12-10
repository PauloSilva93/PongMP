#pragma once
#include "Engine/Core/Layers/layers.hpp"
#include <vector>

namespace Core {

    class LayerStack {

        public:
            LayerStack() = default;
            ~LayerStack();

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* overlay);
            void PopLayer(Layer* layer);
            void PopOverlay(Layer* overlay);

            std::vector<Layer*>::iterator begin() { return this->layers.begin(); };
            std::vector<Layer*>::iterator end()   { return this->layers.end();   };

        private:
            std::vector<Layer*> layers;
            unsigned int layerInsertIndex = 0;

    };

};