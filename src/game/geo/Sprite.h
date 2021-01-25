#pragma once

#include "Rect.h"
#include "../Entity.h" 
#include "glm/glm.hpp"

#include <memory>

#include "renderer/OpenGL/opl.h"


using namespace gl;

class Sprite
{
private:
	glm::vec4 color;
	float size;
	Rect Size;
	Vertex vertex[4];
	unsigned int indices[6];
	float TexId;
	
	void SetPos(float x, float y, float w = 75.0f, float h = 75.0f);
public:
	Sprite( float x, float y, float TexId = 0.0f, float w = 75.0f, float h = 75.0f);
	~Sprite();

	void Draw(render::Renderer& renderer);
	void SetTranslation(glm::vec3 Translation);
	void SetSize(glm::vec3 scale);
	glm::vec2 GetSizeF();
};