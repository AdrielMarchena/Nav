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
	glm::vec3 Position;
	glm::vec3 Velocity;
	TypeEntity Type;
	Rect rect;
	glm::vec3 Scale;
	bool spawned;
public:
	Entity()
		:Position(0.0f,0.0f,0.0f),
		 Velocity(0.0f, 0.0f,0.0f),
		 Type(TypeEntity::DEFAULT)
	{};
	~Entity() {};

	virtual void Update(float deltaTime) {}
	virtual void Draw(render::Renderer& renderer) { }
	virtual TypeEntity GetType() { return Type; };
	virtual bool IsSpawned() { return spawned; };
	virtual glm::vec3 GetScale() { return Scale; }
	virtual glm::vec3 GetPosition() { return Position; }
	virtual void ColisionCallBack(Entity* cause) {  }
};