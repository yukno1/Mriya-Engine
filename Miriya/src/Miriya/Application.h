#pragma once

#include "Core.h"

#include "Miriya/Events/Event.h"
#include "Window.h"
#include "Miriya/Events/ApplicationEvent.h"
#include "Miriya/LayerStack.h"

namespace Miriya {
    class MIR_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // To be defined in client
    Application* CreateApplication();
}




