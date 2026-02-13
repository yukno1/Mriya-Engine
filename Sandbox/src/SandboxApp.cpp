#include <Miriya.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

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

        Miriya::Ref<Miriya::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Miriya::VertexBuffer::Create(vertices, sizeof(vertices)));
        Miriya::BufferLayout layout = {
            {Miriya::ShaderDataType::Float3, "a_Position"},
            {Miriya::ShaderDataType::Float4, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        Miriya::Ref<Miriya::IndexBuffer> indexBuffer;
        indexBuffer.reset(Miriya::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(Miriya::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        Miriya::Ref<Miriya::VertexBuffer> squareVB;
        squareVB.reset(Miriya::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
            {Miriya::ShaderDataType::Float3, "a_Position"},
            {Miriya::ShaderDataType::Float2, "a_TexCoord"}
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Miriya::Ref<Miriya::IndexBuffer> squareIB;
        squareIB.reset(Miriya::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);


        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
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

        m_Shader.reset(Miriya::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorShaderVertexSrc = R"(
            #version 460 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
            }
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 460 core
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main() {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_FlatColorShader.reset(Miriya::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main() {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string textureShaderFragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main() {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        m_TextureShader.reset(Miriya::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

        m_Texture = Miriya::Texture2D::Create("../../Sandbox/assets/textures/Checkerboard.png");
        m_ChernoLogoTexture = Miriya::Texture2D::Create("../../Sandbox/assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Miriya::Timestep timestep) override {

        if (Miriya::Input::IsKeyPressed(MIR_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed* timestep;
        }

        if (Miriya::Input::IsKeyPressed(MIR_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed* timestep;
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed* timestep;
        }

        if (Miriya::Input::IsKeyPressed(MIR_KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed* timestep;
        }
        else if (Miriya::Input::IsKeyPressed(MIR_KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed* timestep;
        }

        // high-level
        Miriya::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Miriya::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        // contain all information about the scene
        // camera, light, environment, ...
        Miriya::Renderer::BeginScene(m_Camera);

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for ( int y {0}; y < 20; ++y) {
            for (int x {0}; x < 20; ++x) {
                glm::vec3 pos {x * 0.11f, y * 0.11f, 0.0f};
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Miriya::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform); // able to overload: submit many types
            }
        }

        m_Texture->Bind();
        Miriya::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_ChernoLogoTexture->Bind();
        Miriya::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // triangle
        // Miriya::Renderer::Submit(m_Shader, m_VertexArray);

        Miriya::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");

        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

        ImGui::End();
    }

    void OnEvent(Miriya::Event& event) override {
    }
private:
    Miriya::Ref<Miriya::Shader> m_Shader;
    Miriya::Ref<Miriya::VertexArray> m_VertexArray;

    Miriya::Ref<Miriya::Shader> m_FlatColorShader, m_TextureShader;
    Miriya::Ref<Miriya::VertexArray> m_SquareVA;

    Miriya::Ref<Miriya::Texture2D> m_Texture, m_ChernoLogoTexture;

    Miriya::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed {2.0f};

    float m_CameraRotation {0.0f};
    float m_CameraRotationSpeed {180.0f};

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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
