#pragma once

#include "Miriya/Renderer/VertexArray.h"

namespace Miriya {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override {return m_VertexBuffers;}
        const Ref<IndexBuffer> &GetIndexBuffer() const override {return m_IndexBuffer;}
    private:
        // reference to all vertex buffers and index buffer
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;

        uint32_t m_RendererID;
    };
} // Miriya