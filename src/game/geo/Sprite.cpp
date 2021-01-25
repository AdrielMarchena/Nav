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

void Sprite::SetPos(float x, float y, float w,float h)
{
	//w *= m_Scale.x;
	vertex[0].Position = { x,y,0.0f };

	vertex[1].Position = { x + w,y,0.0f };

	vertex[2].Position = { x + w,y + h,0.0f };

	vertex[3].Position = { x, y + h, 0.0f };
}

Sprite::Sprite(float x, float y, float TexId, float w, float h)
	:color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
	Size({x,y,w,h}),
	TexId(TexId),
	size(w)
{
	SetPos(x, y, Size.w,Size.h);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
		
}

Sprite::~Sprite()
{
}

void Sprite::Draw(render::Renderer& renderer)
{
	SetPos(Size.x, Size.y,Size.w, Size.h);

	render::Renderer::PushInVertexB({ vertex[0],vertex[1],vertex[2],vertex[3]});
}
