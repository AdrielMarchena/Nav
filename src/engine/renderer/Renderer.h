#pragma once

#include <GL/glew.h>

#define ASSERT(x) if(!(x))__debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"

namespace render {
    class Renderer
    {
    private:
        Renderer() {}
        Renderer(Renderer const&) = delete;
        void operator = (Renderer const&) = delete;
    public:
        static Renderer& getInstance() { static Renderer instance; return instance; }
        static void Clear();
        static void Draw(const gl::VertexArray& va, const gl::IndexBuffer& ib, const gl::Shader& shader);
    };
}