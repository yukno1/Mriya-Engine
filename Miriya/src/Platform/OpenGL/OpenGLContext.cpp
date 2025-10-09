#include "mirpch.h"
#include "OpenGLContext.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include "Miriya/Core.h"

namespace Miriya {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle){
        MIR_CORE_ASSERT(windowHandle, "windowHandle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGL(glfwGetProcAddress);
        MIR_CORE_ASSERT(status, "Failed to initialize GLAD!");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
} //Miriya
