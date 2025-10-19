#include "mirpch.h"
#include "Renderer.h"

namespace Miriya {

    Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData;

    // make sure shader gets right uniforms
    // environment map; cube map; camera; light; material; model; etc
    void Renderer::BeginScene(OrthographicCamera &camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    // submit into render queue
    void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        // submit per object; queue
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        // just render command; can't do multiple things
        RenderCommand::DrawIndexed(vertexArray);
    }
} // Miriya
