#include "mirpch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"
#include "Miriya/Core.h"

namespace Miriya {
    VertexBuffer * VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: MIR_CORE_ASSERT(false, "Renderer::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer * IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: MIR_CORE_ASSERT(false, "Renderer::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }
        MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
