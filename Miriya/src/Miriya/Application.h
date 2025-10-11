#pragma once

#include "Core.h"

#include "Window.h"
#include "Miriya/LayerStack.h"
#include "Miriya/Events/Event.h"
#include "Miriya/Events/ApplicationEvent.h"

#include "Miriya/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

namespace Miriya {
    class MIR_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        // imgui layer automatically added by Miriya runtime
        ImGuiLayer* m_ImGuiLayer;

        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;

        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    };

    // To be defined in client
    Application* CreateApplication();
} // Miriya




