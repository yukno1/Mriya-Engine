#pragma once

#include "Core.h"

namespace Miriya {
    class MIR_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in client
    Application* CreateApplication();
}




