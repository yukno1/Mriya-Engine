#pragma once

#include <string>

namespace Miriya {
    class Shader {
    public:
        // Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader() = default;

        // In the future, want to have subclasses; Implemented per API; so need to be virtual
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0; // for debugging purposes

        // not want to expose these
        // void UploadUniformFloat4(const std::string &name, const glm::vec4& values);
        // void UploadUniformMat4(const std::string &name, const glm::mat4& matrix);

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
} // Miriya