#include "Spawner.h"
#include "Game.h"
Spawner::Spawner()
{
	for (int i = 0; i < 5; i++)
	{
		auto a = new Enemy();
		enemy_list.push_back(a);
		Game::PushEntity(a);
		Game::PushIntoColisor(a);
	}
}

void Spawner::SpawnEnemy()
{
	static int count = 125;
	for (auto& i : enemy_list)
	{
		if (!i->IsSpawned() && count < 1)
			if (P_random() < 1 || P_random() > 254 || (P_random() < 100 && P_random() > 98))
			{
					//int gW = (int)Game::GetScreenSize().w;
					//int gH = (int)Game::GetScreenSize().h;
					int gW = 1;
					int gH = 1;
					int randX = (P_random() / 1000) & 1;
					if (randX < 0.1f)
						randX += (i->GetScale().x * 1.0f) + 1.0f;
					if (randX + (i->GetScale().x * 1.0f) > 1.0f)
						randX -= (i->GetScale().x * 1.0f) + 1.0f;
					i->Spawn(0.5f, 1.0f + 1.0f);
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