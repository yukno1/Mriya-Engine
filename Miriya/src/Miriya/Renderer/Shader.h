#pragma once

#include <string>

namespace Miriya {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        // In the future, want to have subclasses; Implemented per API; so need to be virtual
        void Bind() const;
        void Unbind() const; // for debugging purposes
    private:
        uint32_t m_RendererID;
    };
} // Miriya