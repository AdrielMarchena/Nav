#include "Spawner.h"
#include "Game.h"
Spawner::Spawner()
{
	for (int i = 0; i < 15; i++)
	{
		auto a = new Enemy();
		enemy_list.push_back(a);
		Game::PushEntity(a);
		Game::PushIntoColisor(a);
	}
}

void Spawner::SpawnEnemy()
{
	static int count = 0;
	for (auto& i : enemy_list)
	{
		if (!i->IsSpawned() && count < 1)
			if (P_random() < 1 || P_random() > 254 || (P_random() < 100 && P_random() > 98))
			{
					int gW = (int)Game::GetScreenSize().w;
					int gH = (int)Game::GetScreenSize().h;
					int randX = (P_random() * 3) & gW;
					if (randX < 50.0f)
						randX += (i->GetScale().x * 50.f) + 50.0f;
					if (randX + (i->GetScale().x * 50.f) > gW)
						randX -= (i->GetScale().x * 50.f) + 50.0f;
					i->Spawn(randX, Game::GetScreenSize().h + 75);
					count = 125;
					break;
			}
	}
	count--;
}

Spawner::~Spawner()
{
	for (auto& i : enemy_list)
		delete i;
	enemy_list.clear();
}