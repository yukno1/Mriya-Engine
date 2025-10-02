#pragma once

#include "Miriya/Layer.h"
#include "Miriya/Events/MouseEvent.h"
#include "Miriya/Events/KeyEvent.h"
#include "Miriya/Events/ApplicationEvent.h"

namespace Miriya {

    class MIR_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;

        // Enable layer to imgui rendering independently
        // begin a new window
        void Begin();
        void End();

        // enclose layer
        void OnImGuiRender() override;
    private:
        float m_Time = 0.0f;
    };
} // Miriya
