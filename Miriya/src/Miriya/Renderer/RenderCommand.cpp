#include "mirpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Miriya {

    // future dynamically setting renderer API
    RendererAPI * RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}