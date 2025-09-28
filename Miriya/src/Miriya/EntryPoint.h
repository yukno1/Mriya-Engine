#pragma once


#ifdef MIR_PLATFORM_WINDOWS

// function returns the application
// creation is implemented in client
// extern means find in somewhere else
//extern Miriya::Application* Miriya::CreateApplication();

int main(int argc, char** argv) {

    // For test, Later move into App
    Miriya::Log::Init();
    MIR_CORE_WARN("Initialized Log");
    int a = 5;
    MIR_INFO("Hello! Var={0}", a);

    auto app = Miriya::CreateApplication();
    app->Run();
    delete app;
}

#endif