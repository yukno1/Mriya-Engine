#include "mirpch.h"
#include "Miriya/Application.h"

#include "Miriya/Events/ApplicationEvent.h"
#include "Miriya/Log.h"
#include <glfw3.h>

namespace Miriya {
    Application::Application() {
        // b/c it's an explicit constructor, we need to type unique ptr
        // unique_ptr means no need to delete the window manually when terminate window
        // since application is obviously a singleton
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }

    }
}

