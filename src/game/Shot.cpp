#include "Shot.h"

#include "Resources.h"
#include "Game.h"
#include "Utils/RandomList.h"
#include "glm/gtc/matrix_transform.hpp"
using namespace engine;
Shot::Shot()
	:shot_sprite( -1.0f, -1.0f, 1.0f)
{
	Type = TypeEntity::PROJ;
	Scale = glm::vec3(0.2f);
	shot_sprite.SetScale(Scale);
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
	Position = { x , y, Position.z };
	maxVelocity = (P_random() & 287) + 287;
	Velocity.y = (P_random() & 275) + 275;
}

void Shot::PutAway()
{
	if (!spawned)
		return;
	spawned = false;
	Position.x = -1.0f;
	Position.y = -1.0f;
	shot_sprite.SetTranslation({ Position.x,Position.y,0 });
}

void Shot::Kill()
{
	PutAway();
}

void Shot::Update(float deltaTime)
{
	if (!spawned)
		return;

	if (Position.y + 15.0f > Game::GetScreenSize().h)
	{
		PutAway();
		return;
	}
	if (Velocity.y < maxVelocity)
		Velocity.y += 0.1f * deltaTime;
	Position.y += Velocity.y * deltaTime;
	shot_sprite.SetTranslation({ Position.x,Position.y,0 });
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
