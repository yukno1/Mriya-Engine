#include "mirpch.h"
#include "Miriya/Application.h"

#include "Miriya/Log.h"
#include <glfw3.h>

namespace Miriya {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        // b/c it's an explicit constructor, we need to type unique ptr
        // unique_ptr means no need to delete the window manually when terminate window
        // since application is obviously a singleton
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_Running) {
            // glClearColor(1, 0, 1, 1);
            // glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        MIR_CORE_TRACE("{0}", e.ToString());
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

}

