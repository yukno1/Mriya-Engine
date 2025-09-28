#include "Miriya/Application.h"

#include "Miriya/Events/ApplicationEvent.h"
#include "Miriya/Log.h"

namespace Miriya {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::Run() {
        WindowResizeEvent e(1200, 720);
        MIR_TRACE("{}", e.ToString());

        while (true);
    }
}

