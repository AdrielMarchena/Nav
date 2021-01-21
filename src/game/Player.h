#pragma once

#include "geo/Sprite.h"
#include "renderer/Renderer.h"
#include <vector>
#include "Shot.h"
#include "geo/Rect.h"
class Player : public Entity, public Rect
{
private:
	Sprite player_sprite;
	std::vector<Shot*> shots;
	unsigned char spawnedShots;
	unsigned char lastSpawnedShots;
public:
	Player();
	~Player();

	void Update(float deltaTime) override;
	void Draw(render::Renderer& render) override;
	void ColisionCallBack(Entity* cause) override;
	void Kill();
private:
	inline void Input(float deltaTime);
	int DeadCount;
};