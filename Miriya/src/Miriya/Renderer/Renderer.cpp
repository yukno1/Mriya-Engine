#include "mirpch.h"
#include "Renderer.h"

namespace Miriya {
    // make sure shader gets right uniforms
    // environment map; cube map; camera; light; material; model; etc
    void Renderer::BeginScene() {
    }

    void Renderer::EndScene() {
    }

    // submit into render queue
    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->Bind();
        // just render command; can't do multiple things
        RenderCommand::DrawIndexed(vertexArray);
    }
} // Miriya
