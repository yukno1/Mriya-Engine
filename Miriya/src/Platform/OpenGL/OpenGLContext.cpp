#include "mirpch.h"
#include "OpenGLContext.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include "Miriya/Log.h"

namespace Miriya {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle){
        MIR_CORE_ASSERT(windowHandle, "windowHandle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGL(glfwGetProcAddress);
        MIR_CORE_ASSERT(status, "Failed to initialize GLAD!");


        MIR_CORE_INFO("OpenGL Info:");
        MIR_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        MIR_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        MIR_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
} //Miriya
