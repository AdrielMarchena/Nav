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
	glm::vec3 m_Translation;

	glm::vec3 m_Scale;
	Vertex vertex[4];
	unsigned int indices[6];
	float TexId;
	
	void SetPos(float x, float y, float TexId = 0.0f, float w = 1.0f);
public:
	Sprite( float x, float y, float TexId = 0.0f, float w = 1.0f, float h = 1.0f);
	~Sprite();

	void Draw(render::Renderer& renderer);
	void SetTranslation(glm::vec3 Translation);
	void SetScale(glm::vec3 scale);
	float GetScaleF();
	glm::vec3 GetScaleV3();
};