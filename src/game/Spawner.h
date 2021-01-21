#pragma once

#include <vector>
#include "Enemy.h"
#include "Utils/RandomList.h"
class Spawner
{
public:
	std::vector<Enemy*> enemy_list;

	Spawner();
	void SpawnEnemy();
	~Spawner();
};