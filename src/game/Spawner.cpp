#include "Spawner.h"
#include "Game.h"
Spawner::Spawner()
{
	for (int i = 0; i < 10; i++)
	{
		auto a = new Enemy();
		enemy_list.push_back(a);
		Game::PushEntity(a);
		//Game::PushIntoColisor(a);
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

					int randX = (P_random() * 5 ) & gW;
					if (randX + i->GetPosition().w > gW)
						randX = gW - i->GetPosition().w - 1.0f - (P_random() & gW);
					if (randX < 0)
						randX = (-randX) + 2.0f;
					i->Spawn(randX, gH + i->GetPosition().h + 55.0f);
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