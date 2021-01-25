#include "Player.h"

#include "input/Keyboard.h"
#include "Resources.h"
#include "Game.h"
#include "glm/gtc/matrix_transform.hpp"
using namespace engine;

Player::Player():
	player_sprite(0.0f, 0.0f, 0.0f , 75.0f)
{
	Type = TypeEntity::PLAYER;
	rect.x = Game::GetScreenSize().w / 2;
	rect.y = Game::GetScreenSize().h / 4;
	Velocity = { 550.0f,550.0f,0.0f };
	DeadCount = 0;

	for (int i = 0; i < 30; i++)
	{
		auto a = new Shot();
		shots.push_back(a);
		Game::PushEntity(a);
		Game::PushIntoColisor(a);
	}
	spawnedShots = 0;
	lastSpawnedShots = 0;
}

Player::~Player()
{
	for (auto& i : shots)
		delete i;
	shots.clear();
}

void Player::Update(float deltaTime)
{
	if (!spawned)
	{
		DeadCount -= 1 * deltaTime;
		if (DeadCount < 1)
			spawned = true;
		return;
	}
	player_sprite.SetTranslation({rect.x, rect.y, 0.0f});
	Input(deltaTime);
}

void Player::Draw(render::Renderer& renderer)
{
	if (spawned)
	player_sprite.Draw(renderer);
}

inline void Player::Input(float deltaTime)
{
	if (DeadCount > 1)
		return;
	using namespace input;
	//float border = player_sprite.GetScaleF() * 50.0f;
	if (Keyboard::isPress(Keyboard::ARROW_LEFT))
	{
		//50 is because is the default value on the Vertices things on the sprite
		//if (Position.x - border >= 0)
			rect.x -= Velocity.x * deltaTime;
	}
	if (Keyboard::isPress(Keyboard::ARROW_RIGHT))
	{
		//if(Position.x + border <= Game::GetScreenSize().w)
			rect.x += Velocity.x * deltaTime;
	}
	Keyboard::clicked(Keyboard::SPACEBAR, [&]() {
		if(spawned)
			for (auto& i : shots)
			{
				if (!i->IsSpawned())
				{
					float Y = rect.y + ( rect.y / 4);
					i->ShotMe(rect.x, rect.y);
					break;
				}
			}
	});
}

void Player::ColisionCallBack(Entity* cause)
{
	if (cause->GetType() == TypeEntity::ENEMY)
	{
		DeadCount = 200;
		spawned = false;
	}
}

void Player::Kill()
{
}
