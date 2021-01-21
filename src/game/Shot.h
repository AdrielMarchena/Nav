#pragma once

#include "Entity.h"
#include "geo/Sprite.h"
#include "renderer/Renderer.h"

class Shot : public Entity
{
public:

	Shot();
	~Shot();

	void ShotMe(float x, float y);
	void PutAway();
	void Kill();

	void Update(float deltaTime) override;
	void Draw(render::Renderer& renderer);
	void ColisionCallBack(Entity* cause) override;
private:
	Sprite shot_sprite;
	int maxVelocity;
};