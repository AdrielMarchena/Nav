#pragma once

#include "Entity.h"
#include "renderer/Renderer.h"
#include "geo/Sprite.h"
class Enemy : public Entity
{
private:
	Sprite enemy_sprite;
	int Life;
public:
	Enemy();
	~Enemy();

	void Update(float deltaTime) override;
	void Draw(render::Renderer& renderer) override;
	void ColisionCallBack(Entity* cause) override;

	void Spawn(float x, float y);
	void Dispawn();
};