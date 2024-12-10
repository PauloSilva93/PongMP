#include "layer-stack.hpp"
#include "Engine/Debug/profiling.hpp"

namespace Core {

    LayerStack::~LayerStack() {

        PROFILE_FUNCTION();

        for (Layer* layer : layers) {
            layer->OnDetach();
            delete layer;
        }


    };

    void LayerStack::PushLayer(Layer* layer) {

        PROFILE_FUNCTION();

        layers.emplace(layers.begin() + layerInsertIndex, layer);
        layerInsertIndex++;

    };

    void LayerStack::PushOverlay(Layer* overlay) {

        PROFILE_FUNCTION();

        layers.emplace_back(overlay);

    };

    void LayerStack::PopLayer(Layer* layer) {

        PROFILE_FUNCTION();

        auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
        if (it != layers.begin() + layerInsertIndex) {

            layer->OnDetach();
        
            layers.erase(it);
        
            layerInsertIndex--;
        
        };

    };

    void LayerStack::PopOverlay(Layer* overlay) {

        PROFILE_FUNCTION();

        auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
        if (it != layers.end()) {

            overlay->OnDetach();
            layers.erase(it);

        };

    };

};