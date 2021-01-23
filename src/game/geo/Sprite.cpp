#include "Sprite.h"
#include "Resources.h"
#include "renderer/Renderer.h"
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

void Sprite::SetPos(float x, float y, float TexId, float w)
{
	w *= m_Scale.x;
	vertex[0].Position = { x,y,0.0f };
	vertex[0].Color = { 0.18f,0.6f,0.96f,1.0f };
	vertex[0].TexCoords = { 0.0f,0.0f };
	vertex[0].TexId = { TexId };

	vertex[1].Position = { x + w,y,0.0f };
	vertex[1].Color = { 0.18f,0.6f,0.96f,1.0f };
	vertex[1].TexCoords = { 1.0f,0.0f };
	vertex[1].TexId = { TexId };

	vertex[2].Position = { x + w,y + w,0.0f };
	vertex[2].Color = { 0.18f,0.6f,0.96f,1.0f };
	vertex[2].TexCoords = { 1.0f,1.0f };
	vertex[2].TexId = { TexId };

	vertex[3].Position = { x, y + w, 0.0f };
	vertex[3].Color = { 0.18f,0.6f,0.96f,1.0f };
	vertex[3].TexCoords = { 0.0f,1.0f };
	vertex[3].TexId = { TexId };
}

Sprite::Sprite(float x, float y, float TexId, float w, float h)
	:color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
	m_Translation(x, y, 0),
	m_Scale(glm::vec3(1.0f)),
	TexId(TexId)
{
	SetPos(x, y,TexId,w);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
		
	render::Renderer::PushInVertexB({ vertex[0],vertex[1],vertex[2],vertex[3] },
		{indices[0], indices[1], indices[2], indices[3], indices[4], indices[5]} );

}

Sprite::~Sprite()
{
	
}

void Sprite::Draw(render::Renderer& renderer)
{
	SetPos(m_Translation.x, m_Translation.y,TexId);

	render::Renderer::PushInVertexB({ vertex[0],vertex[1],vertex[2],vertex[3] },
		{ indices[0], indices[1], indices[2], indices[3], indices[4], indices[5] });
}
