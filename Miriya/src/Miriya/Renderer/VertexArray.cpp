#include "mirpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Miriya {

    VertexArray * VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: MIR_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }
        MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}