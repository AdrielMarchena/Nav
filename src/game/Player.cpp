#include "Player.h"

#include "input/Keyboard.h"
#include "Resources.h"
#include "Game.h"
#include "glm/gtc/matrix_transform.hpp"
using namespace engine;

Player::Player():
	player_sprite(0.0f, 0.0f, 0.0f , 65.0f, 65.0f)
{
	Type = TypeEntity::PLAYER;
	rect.x = Game::GetScreenSize().w / 2;
	rect.y = 65.0f;
	rect.w = 65.0f;
	rect.h = 65.0f;
	player_sprite.SetTranslation({ rect.x,rect.y,0.0f });
	Velocity = { 550.0f,550.0f,0.0f };
	DeadCount = 0;

	for (int i = 0; i < 60; i++)
	{
		auto a = new Shot();
		shots.push_back(a);
		Game::PushEntity(a);
		//Game::PushIntoColisor(a);
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
	//std::cout << "Screen Size W < " << Game::GetScreenSize().w << " > H < " << Game::GetScreenSize().h << " >" << std::endl;
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
	float gW = Game::GetScreenSize().w;
	float gH = Game::GetScreenSize().h;
	if (Keyboard::isPress(Keyboard::ARROW_LEFT))
	{
		if(rect.x > 0.0f)
		rect.x -= Velocity.x * deltaTime;
	}
	if (Keyboard::isPress(Keyboard::ARROW_RIGHT))
	{
		if(rect.x + rect.w < gW)
		rect.x += Velocity.x * deltaTime;
	}
	if (Keyboard::isPress(Keyboard::ARROW_UP))
	{
		if(rect.y + rect.h < gH)
		rect.y += Velocity.y * deltaTime;
	}
	if (Keyboard::isPress(Keyboard::ARROW_DOWN))
	{
		if(rect.y > 0)
		rect.y -= Velocity.y * deltaTime;
	}
	Keyboard::clicked(Keyboard::S_KEY, [&]() {
		static unsigned int tex = 0;
		tex++;
		player_sprite.SetTexId(tex % 2);
	});
	Keyboard::clicked(Keyboard::SPACEBAR, [&]() {
		if(spawned)
			for (auto& i : shots)
			{
				if (!i->IsSpawned())
				{
					float X = (rect.x + (rect.w / 2)) - (i->GetPosition().w / 2);
					i->ShotMe(X, rect.y);
					Speaker[0].Play(Resources::GetSound("shot_sound"));
					break;
				}
			}
	});
	if (Keyboard::isPress(Keyboard::A_KEY))
	{
		if (spawned)
			for (auto& i : shots)
			{
				if (!i->IsSpawned())
				{
					float RandX = ((P_random() + (int)(rect.w / 12)) & (int)(rect.w - i->GetPosition().w));
					i->ShotMe(rect.x + RandX, rect.y);
					break;
				}
			}
	}
}

void Player::ColisionCallBack(Entity* cause)
{
 	if (cause->GetType() == TypeEntity::ENEMY)
	{
		DeadCount = 200;
		spawned = false;
		Speaker[1].Play(Resources::GetSound("boom_sound"));
	}
}

void Player::Kill()
{
}
