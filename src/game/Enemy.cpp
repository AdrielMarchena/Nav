#include "Enemy.h"

#include "Resources.h"
#include "Game.h"
using namespace engine;
Enemy::Enemy()
	:enemy_sprite(-100.0f, -100.0f, 2.0f,0.0f)
{
	rect.w = 60.0f;
	rect.h = 60.0f;
	Type = TypeEntity::ENEMY;
	spawned = false;
	enemy_sprite.SetSize({ rect.w, rect.h,0.0f });
	Velocity.y = 335.0f;
	Life = 30;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	if (!spawned)
		return;

	if (Life < 1)
		Dispawn();
	if ( rect.y + rect.h < 0)
		Dispawn();

	rect.y -= Velocity.y * deltaTime;
	enemy_sprite.SetTranslation({rect.x,rect.y,0.0f});
}

void Enemy::Draw(render::Renderer& renderer)
{
	if(spawned)
	enemy_sprite.Draw(renderer);
}

void Enemy::ColisionCallBack(Entity* cause)
{
	if (cause->GetType() == TypeEntity::PROJ)
	{
		int a = (P_random() & 12);
 		Life -= a + 7;
	}
	if (cause->GetType() == TypeEntity::PLAYER)
	{
		Dispawn();
	}
}

void Enemy::Spawn(float x, float y)
{
	spawned = true;
	rect.x = x;
	rect.y = y;
	Life = 30;
	enemy_sprite.SetTranslation({ rect.x,rect.y,0.0f });
}

void Enemy::Dispawn()
{
	spawned = false;
	rect.x = -100.0f;
	rect.y = -100.0f;
}
