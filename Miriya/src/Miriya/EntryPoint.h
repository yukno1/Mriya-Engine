#pragma once


#ifdef MIR_PLATFORM_WINDOWS

// function returns the application
// creation is implemented in client
// extern means find in somewhere else
//extern Miriya::Application* Miriya::CreateApplication();

int main(int argc, char** argv) {
    auto app = Miriya::CreateApplication();
    app->Run();
    delete app;
}

#endif