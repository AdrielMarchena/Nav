#pragma once
#include "glm/glm.hpp"
#include "renderer/Renderer.h"
#include "geo/Rect.h"
enum class TypeEntity : uint8_t
{
	DEFAULT,
	PLAYER,
	ENEMY,
	PROJ
};

class Entity
{
protected:
	glm::vec3 Velocity;
	TypeEntity Type;
	Rect rect;
	bool spawned;
public:
	Entity():
		 Velocity(0.0f, 0.0f,0.0f),
		 Type(TypeEntity::DEFAULT)
	{};
	~Entity() {};

	virtual void Update(float deltaTime) {}
	virtual void Draw(render::Renderer& renderer) { }
	virtual TypeEntity GetType() { return Type; };
	virtual bool IsSpawned() { return spawned; };
	virtual Rect GetPosition() { return rect; }
	virtual void ColisionCallBack(Entity* cause) {  }
};