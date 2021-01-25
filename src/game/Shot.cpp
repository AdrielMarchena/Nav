#include "Shot.h"

#include "Resources.h"
#include "Game.h"
#include "Utils/RandomList.h"
#include "glm/gtc/matrix_transform.hpp"
using namespace engine;
Shot::Shot()
	:shot_sprite( -10.0f, -10.0f, 1.0f ,0.1f)
{
	Type = TypeEntity::PROJ;
	rect.w = 45.0f;
	rect.h = 45.0f;
	shot_sprite.SetSize({rect.w,rect.h,0.0f});
	spawned = false;
	Velocity = {0.0f,1.0f,0.0f};
}

Shot::~Shot()
{
}

void Shot::ShotMe(float x, float y)
{
	if (spawned)
		return;
	spawned = true;
	rect.x = x;
	rect.y = y;
	maxVelocity = (P_random() + 245) & 290;
	Velocity.y = (P_random() + 225) & 255;
}

void Shot::PutAway()
{
	if (!spawned)
		return;
	spawned = false;
	rect.x = -10.0f;
	rect.y = -10.0f;
	shot_sprite.SetTranslation({ rect.x,rect.y,0 });
}

void Shot::Kill()
{
	PutAway();
}

void Shot::Update(float deltaTime)
{
	if (!spawned)
		return;

	if (rect.y - rect.h > Game::GetScreenSize().h)
	{
		PutAway();
		return;
	}
	if (Velocity.y < maxVelocity)
		Velocity.y += 99.0f;
	rect.y += Velocity.y * deltaTime;
	shot_sprite.SetTranslation({ rect.x,rect.y,0 });
}

void Shot::Draw(render::Renderer& renderer)
{
	if (spawned)
	shot_sprite.Draw(renderer);
}

void Shot::ColisionCallBack(Entity* cause)
{
	if (cause->GetType() == TypeEntity::ENEMY)
	{
		PutAway();
	}
}
