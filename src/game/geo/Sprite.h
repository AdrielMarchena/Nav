#pragma once

#include "Rect.h"
#include "../Entity.h" 
#include "glm/glm.hpp"

#include <memory>

#include "renderer/OpenGL/opl.h"


using namespace gl;

class Sprite : public Rect
{
private:
	glm::vec4 color;
	glm::mat4 m_View;
	glm::vec3 m_Translation;

	glm::vec3 m_Scale;

	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	Shader* m_Shader;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	Texture* m_Texture;
public:
	Sprite(Shader* shader,Texture* texture,float x = 0.0f, float y = 0.0f, float w = 0.0f, float h= 0.0f);
	~Sprite();

	void Draw(render::Renderer& renderer);
	void SetTranslation(glm::vec3 Translation);
	void SetScale(glm::vec3 scale);
	float GetScaleF();
	glm::vec3 GetScaleV3();
};