#include "Spawner.h"
#include "Game.h"
Spawner::Spawner()
{
	for (int i = 0; i < 10; i++)
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
					int gW = (int)Game::GetScreenSize().w;
					int gH = (int)Game::GetScreenSize().h;

					int randX = (P_random() + (int)(i->GetPosition().w * 2)) & gW - (int)(i->GetPosition().w * 2);
					i->Spawn(randX, gH + (i->GetPosition().w * 2) + 25.0f);
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