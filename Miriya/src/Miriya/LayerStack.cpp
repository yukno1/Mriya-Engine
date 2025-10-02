#include "mirpch.h"
#include "LayerStack.h"

namespace Miriya {

    // owned by application
    LayerStack::LayerStack() {
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        ++m_LayerInsertIndex;
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer) {
        if (const auto it = std::ranges::find(m_Layers, layer); it != m_Layers.end()) {
            m_Layers.erase(it);
            --m_LayerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay) {
        if (const auto it = std::ranges::find(m_Layers, overlay); it != m_Layers.end()) {
            m_Layers.erase(it);
        }
    }

} // Miriya