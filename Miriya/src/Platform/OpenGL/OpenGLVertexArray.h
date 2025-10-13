#pragma once

#include "Miriya/Renderer/VertexArray.h"

namespace Miriya {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override {return m_VertexBuffers;}
        const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override {return m_IndexBuffer;}
    private:
        // reference to all vertex buffers and index buffer
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

        uint32_t m_RendererID;
    };
} // Miriya