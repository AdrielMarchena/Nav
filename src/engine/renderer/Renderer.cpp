#include "Renderer.h"
#include <iostream>

void GLClearError() 
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) 
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] ( " << error << " ): " << function << file << ": " << line << std::endl;
        return false;
    }
    return true;
}
namespace render {

    void Renderer::Clear()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Draw(const gl::VertexArray& va, const gl::IndexBuffer& ib, const gl::Shader& shader)
    {
        shader.Bind();
        va.Bind();
        ib.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

}