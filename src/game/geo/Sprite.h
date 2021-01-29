#pragma once

#include "Rect.h"
#include "../Entity.h" 
#include "glm/glm.hpp"

#include <memory>

#include "renderer/OpenGL/opl.h"


using namespace gl;

struct SpriteCoords
{
	float bX, bY, tX, tY;
};

class Sprite
{
private:
	Rect Size;
	Vertex vertex[4];
	void SetPos(float x, float y, float z = 0.0f ,float w = 75.0f, float h = 75.0f);
public:
	Sprite( float x, float y, float TexId = 0.0f, float w = 75.0f, float h = 75.0f,float z = 0.0f);
	~Sprite();

	void SetTexId(float texId);
	void Draw(render::Renderer& renderer);
	void SetTranslation(glm::vec3 Translation);
	void SetSize(glm::vec3 scale);
	void SetTexCoords(SpriteCoords coords);
	glm::vec2 GetSizeF();
};