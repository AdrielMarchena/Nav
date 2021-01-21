#include "Sprite.h"
#include "Resources.h"
#include "input/Keyboard.h"

#include "glm/gtc/matrix_transform.hpp"

#include "../Game.h"

void Sprite::SetTranslation(glm::vec3 Translation)
{
	m_Translation = Translation;
}

void Sprite::SetScale(glm::vec3 scale)
{
	m_Scale = scale;
}
/* I return only 1 member here because the 3 values of scale are the same */
float Sprite::GetScaleF()
{
	return m_Scale.x;
}

glm::vec3 Sprite::GetScaleV3()
{
	return m_Scale;
}

Sprite::Sprite(Shader* shader, Texture* texture,float x, float y, float w, float h)
	:color(glm::vec4(0.0f,0.0f,0.0f,0.0f)),
	 m_Shader(shader),
	 m_Texture(texture),
	 m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	 m_Translation(x, y, 0),
	 m_Scale(glm::vec3(1.0f))
{
	float vertices[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, //0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f
	};

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
	m_VertexBuffer->Bind();

	unsigned int indices[] = {
			0 , 1 , 2,
			2 , 3 , 0
	};

	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_VertexArray = std::make_unique<VertexArray>();
	m_VertexArray->Bind();
	m_VertexArray->AddBuffer(*m_VertexBuffer,layout);

	m_Shader->Bind();

	m_Texture->Bind();

	m_Shader->SetUniform1i("u_Texture", 0);
}

Sprite::~Sprite()
{
	delete m_Shader;
}

void Sprite::Draw(render::Renderer& renderer)
{
	m_Texture->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
	model = glm::scale(model, m_Scale);
	glm::mat4 mvp = Game::GetProjection() * m_View * model;
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}
