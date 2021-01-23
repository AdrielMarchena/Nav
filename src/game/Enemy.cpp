#include "Enemy.h"

#include "Resources.h"
#include "Game.h"
using namespace engine;
Enemy::Enemy()
	:enemy_sprite(-100.0f, -100.0f, 2.0f)
{
	Type = TypeEntity::ENEMY;
	spawned = false;
	Velocity.y = 1.0f;
	Scale = glm::vec3(0.2f);
	enemy_sprite.SetScale(Scale);
	Life = 30;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	if (!spawned)
		return;

	float border = enemy_sprite.GetScaleF();

	if (Life < 1)
		Dispawn();
	if ( Position.y + border + 10.0f < 0)
		Dispawn();

	Position.y -= Velocity.y * deltaTime;
	enemy_sprite.SetTranslation(Position);
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
 		Life -= a + 10;
	}
	if (cause->GetType() == TypeEntity::PLAYER)
	{
		Dispawn();
	}
}

void Enemy::Spawn(float x, float y)
{
	spawned = true;
	Position.x = x;
	Position.y = y;
	Life = 30;
	enemy_sprite.SetTranslation(Position);
}

void Enemy::Dispawn()
{
	spawned = false;
	Position.x = -100.0f;
	Position.y = -100.0f;
}
