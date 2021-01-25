#include "Renderer.h"
#include <iostream>
#include "Resources.h"
#include "glm/gtc/matrix_transform.hpp"

#include "../game/Game.h"

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
        Renderer::getInstance().IClear();
    }

    void Renderer::Draw()
    {
        Renderer::getInstance().IDraw();
    }

    void Renderer::Init()
    {
        Renderer::getInstance().IInit();
    }

    void Renderer::PushInVertexB(std::array<Vertex, 4> V)
    {
        Renderer::getInstance().IPushInVertexB(V);
    }

    void Renderer::IInit()
    {
        const size_t MaxQuadCount = 1000;
        const size_t MaxVertexCount = 4 * MaxQuadCount;
        const size_t MaxIndexCount = MaxQuadCount * 6;

        GLCall(glGenVertexArrays(1, &VertexArrayId));
        GLCall(glBindVertexArray(VertexArrayId));

        GLCall(glGenBuffers(1, &VertexBufferId));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_STATIC_DRAW));
    
        vertexData.reserve(MaxVertexCount);

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex), (const void*)offsetof(Vertex,Position)));
    
        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));
    
        GLCall(glEnableVertexAttribArray(2));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords)));
    
        GLCall(glEnableVertexAttribArray(3));
        GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexId)));
        
        uint32_t indice[MaxIndexCount];
        uint32_t offset = 0;
        for (size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indice[i + 0] = 0 + offset;
            indice[i + 1] = 1 + offset;
            indice[i + 2] = 2 + offset;

            indice[i + 3] = 2 + offset;
            indice[i + 4] = 3 + offset;
            indice[i + 5] = 0 + offset;

            offset += 4;
        }

        GLCall(glGenBuffers(1, &IndexBufferId));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indice), indice, GL_STATIC_DRAW));

        m_Shader = new gl::Shader("src/engine/renderer/shader/Adv.shader");
        m_Shader->Bind();
        Texs[0] = engine::Resources::GetTexture("Frog")->GetId();
        Texs[1] = engine::Resources::GetTexture("Test")->GetId();
        Texs[2] = engine::Resources::GetTexture("Nave")->GetId();
        auto loc = glGetUniformLocation(m_Shader->GetId(), "u_Textures");
        int samplers[3] = { 0,1,2 };
        glUniform1iv(loc, 3, samplers);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texs[0]);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texs[1]);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texs[2]);

    }

    void Renderer::IClear()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        delete m_Shader;
    }

    void Renderer::IPushInVertexB(std::array<Vertex,4> V)
    {
        //static unsigned int LastV = 0, LastI = 0;
        for (auto& v : V)
            vertexData.push_back(v);
        IndicesCount += 6;
        //LastV += V.size();
        //LastI += I.size();
    }

    void Renderer::IDraw()
    {
        static double count = 0;
        count++;
        if (count >= 50)
            std::cout << "";
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_ViewProj", Game::GetProjection());
        m_Shader->SetUniformMat4f("u_Transform", glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f)));

        //std::cout << "Pointer" << sizeof(vertexData.data()) << std::endl;
        //std::cout << "Vector" << indices.size() << std::endl;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0 , vertexData.size() * sizeof(Vertex), vertexData.data()));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId));
        GLCall(glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, nullptr));
        m_Shader->Unbind();
        vertexData.clear();
        IndicesCount = 0;
        vertexData.reserve(1000);
    }
}