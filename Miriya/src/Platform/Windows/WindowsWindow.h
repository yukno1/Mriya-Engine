#pragma once

#include "Miriya/Window.h"



struct GLFWwindow;

namespace Miriya {

    class WindowsWindow : public Window {
    public:
        explicit WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        [[nodiscard]] inline unsigned int GetWidth() const override { return m_Data.Width; }
        [[nodiscard]] inline unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        [[nodiscard]] bool IsVSync() const override;

        inline void* GetNativeWindow() const override { return m_Window; };
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;

        // might be requested when glfw callback
        // group window-specific data, so no need to return whole class
        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}