#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Miriya {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        // In the future, want to have subclasses; Implemented per API; so need to be virtual
        void Bind() const;
        void Unbind() const; // for debugging purposes

        void UploadUniformMat4(const std::string &name, const glm::mat4& matrix);
    private:
        uint32_t m_RendererID;
    };
} // Miriya