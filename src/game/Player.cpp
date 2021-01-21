#include "Player.h"

#include "input/Keyboard.h"
#include "Resources.h"
#include "Game.h"
using namespace engine;

Player::Player():
	player_sprite(Resources::GetShader("adv"), Resources::GetTexture("Test"), Game::GetScreenSize().w / 2, Game::GetScreenSize().h / 2)
{
	Type = TypeEntity::PLAYER;
	Position.x = Game::GetScreenSize().w / 2;
	Position.y = Game::GetScreenSize().h / 4;
	Velocity = { 550.0f,250.f,0.0f };
	Scale = glm::vec3(0.8f);
	player_sprite.SetScale(Scale);
	DeadCount = 0;

	for (int i = 0; i < 10; i++)
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
		DeadCount--;
		if (DeadCount < 1)
			spawned = true;
		return;
	}
	Input(deltaTime);
	player_sprite.SetTranslation({ Position.x,Position.y,0 });
}

void Player::Draw(render::Renderer& renderer)
{
	if (!spawned)
		return;
	player_sprite.Draw(renderer);
}

inline void Player::Input(float deltaTime)
{
	if (DeadCount > 1)
		return;
	using namespace input;
	float border = player_sprite.GetScaleF() * 50.0f;
	if (Keyboard::isPress(Keyboard::ARROW_LEFT))
	{
		//50 is because is the default value on the Vertices things on the sprite
		if (Position.x - border >= 0)
			Position.x -= Velocity.x * deltaTime;
	}
	if (Keyboard::isPress(Keyboard::ARROW_RIGHT))
	{
		if(Position.x + border <= Game::GetScreenSize().w)
			Position.x += Velocity.x * deltaTime;
	}
	Keyboard::clicked(Keyboard::SPACEBAR, [&]() {
		if(spawned)
			for (auto& i : shots)
			{
				if (!i->IsSpawned())
				{
					float Y = Position.y + ( border / 4);
					i->ShotMe(Position.x, Position.y);
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
