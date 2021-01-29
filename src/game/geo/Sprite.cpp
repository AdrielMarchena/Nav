#include "Sprite.h"
#include "Resources.h"
#include "renderer/Renderer.h"
#include "input/Keyboard.h"

#include "glm/gtc/matrix_transform.hpp"

#include "../Game.h"

void Sprite::SetTranslation(glm::vec3 Translation)
{
	Size.x = Translation.x;
	Size.y = Translation.y;
	Size.z = Translation.z;
}

void Sprite::SetSize(glm::vec3 scale)
{
	Size.w = scale.x;
	Size.h = scale.y;
}
/* I return only 1 member here because the 3 values of scale are the same */
glm::vec2 Sprite::GetSizeF()
{
	return {Size.w,Size.h};
}

void Sprite::SetPos(float x, float y, float z, float w, float h)
{
	//w *= m_Scale.x;
	vertex[0].Position = { x,y,z };

	vertex[1].Position = { x + w,y,z };

	vertex[2].Position = { x + w,y + h,z };

	vertex[3].Position = { x, y + h, z };
}

void Sprite::SetTexCoords(SpriteCoords coords)
{
	//float divid = 1.0f / 64.0f;
	//float bX = 0.0f;
	//float tX = divid * 16.0f;
	//float bY = (40.0f * divid);
	//float tY = 1.0f;
	vertex[0].TexCoords = { coords.bX,coords.bY }; // Bottom Left
	vertex[1].TexCoords = { coords.tX ,coords.bY }; // Bottom Right
	vertex[2].TexCoords = { coords.tX,coords.tY }; // Top Right
	vertex[3].TexCoords = { coords.bX,coords.tY }; // Top Left
	/*vertex[0].TexCoords = { 0.0f,0.0f };
	vertex[1].TexCoords = { 1.0f + x,0.0f };
	vertex[2].TexCoords = { 1.0f + x,1.0f + y };
	vertex[3].TexCoords = { 0.0f,1.0f + y };*/
}

void Sprite::SetTexId(float texId)
{
	vertex[0].TexId = texId;
	vertex[1].TexId = texId;
	vertex[2].TexId = texId;
	vertex[3].TexId = texId;
}

Sprite::Sprite(float x, float y, float TexId, float w, float h, float z):
	Size({x,y,w,h})
{
	SetPos(x, y,z,Size.w,Size.h);
	SetTexCoords({ 0.0f,0.0f,1.0f,1.0f });
	SetTexId(TexId);
}

Sprite::~Sprite()
{
}

void Sprite::Draw(render::Renderer& renderer)
{
	SetPos(Size.x, Size.y,Size.z,Size.w, Size.h);
	render::Renderer::PushInVertexB({ vertex[0],vertex[1],vertex[2],vertex[3]});
}
