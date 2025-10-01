#include "mirpch.h"
#include "Miriya/Application.h"

#include "Miriya/Log.h"
#include <../../vendor/GLFW/glfw3.h>

#include "Miriya/Input.h"

namespace Miriya {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        MIR_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        // b/c it's an explicit constructor, we need to type unique ptr
        // unique_ptr means no need to delete the window manually when terminate window
        // since application is obviously a singleton
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() = default;

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
        // dispatcher.Dispatch<WindowCloseEvent>([this](auto && PH1) { return OnWindowClosed(std::forward<decltype(PH1)>(PH1)); });

        MIR_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            // go backwards stack
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run() {
        while (m_Running) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色和深度缓冲区

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            auto[x, y] = Input::GetMousePosition();
            MIR_CORE_TRACE("{0}, {1}", x, y);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

}

