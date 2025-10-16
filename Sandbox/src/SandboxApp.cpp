#include <Miriya.h>

#include "imgui.h"

class ExampleLayer : public Miriya::Layer {
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        m_VertexArray.reset(Miriya::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        std::shared_ptr<Miriya::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Miriya::VertexBuffer::Create(vertices, sizeof(vertices)));
        Miriya::BufferLayout layout = {
            {Miriya::ShaderDataType::Float3, "a_Position"},
            {Miriya::ShaderDataType::Float4, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<Miriya::IndexBuffer> indexBuffer;
        indexBuffer.reset(Miriya::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(Miriya::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
        };

        std::shared_ptr<Miriya::VertexBuffer> squareVB;
        squareVB.reset(Miriya::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
            {Miriya::ShaderDataType::Float3, "a_Position"},
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Miriya::IndexBuffer> squareIB;
        squareIB.reset(Miriya::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);


        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(new Miriya::Shader(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_Shader2.reset(new Miriya::Shader(vertexSrc2, fragmentSrc2));
    }

    void OnUpdate() override {

        if (Miriya::Input::IsKeyPressed(MIR_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed;  // future get delta time
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed;
        }

        if (Miriya::Input::IsKeyPressed(MIR_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed;
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed;
        }

        if (Miriya::Input::IsKeyPressed(MIR_KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed;
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed;
        }

        // high-level
        Miriya::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Miriya::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        // contain all information about the scene
        // camera, light, environment, ...
        Miriya::Renderer::BeginScene(m_Camera);

        Miriya::Renderer::Submit(m_Shader2, m_SquareVA); // able to overload: submit many types
        Miriya::Renderer::Submit(m_Shader, m_VertexArray);

        Miriya::Renderer::EndScene();

        // Renderer::Flush();
    }

    void OnImGuiRender() override {}

    void OnEvent(Miriya::Event& event) override {
    }
private:
    std::shared_ptr<Miriya::Shader> m_Shader;
    std::shared_ptr<Miriya::VertexArray> m_VertexArray;

    std::shared_ptr<Miriya::Shader> m_Shader2;
    std::shared_ptr<Miriya::VertexArray> m_SquareVA;

    Miriya::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed {0.1f};

    float m_CameraRotation {0.0f};
    float m_CameraRotationSpeed {0.1f};
};


class Sandbox : public Miriya::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};


Miriya::Application* Miriya::CreateApplication() {
    return new Sandbox();
}
