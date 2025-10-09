#pragma once

#include "Miriya/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Miriya {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}