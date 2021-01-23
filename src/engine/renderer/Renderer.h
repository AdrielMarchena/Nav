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
#include "OpenGL/Vertex.h"
#include <vector>
#include <array>

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
        static void Draw();
        static void Init();
        static void PushInVertexB(std::array<Vertex, 4> V, std::array<unsigned int, 6> I);

    private:
        void IInit();
        void IClear();
        unsigned int VertexBufferId = 0;
        unsigned int VertexArrayId = 0;
        unsigned int IndexBufferId = 0;
        unsigned int Texs[32];
        gl::Shader* m_Shader;

        void IPushInVertexB(std::array<Vertex, 4> V, std::array<unsigned int, 6> I);
        void IDraw();
        std::vector<Vertex> vertexData;
        std::vector<unsigned int> indices;
    };
}