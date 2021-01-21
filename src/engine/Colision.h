#pragma once
#include <vector>

#include "../game/Entity.h"
#include <functional>
namespace engine
{
	class Colision
	{
	private:
		std::vector<Entity*> entitys;
		std::function<bool(Entity* f, Entity* c)> test_function;
	public:
		Colision(std::vector<Entity*> entitys, std::function<bool(Entity* f, Entity* c)> test_function);
		Colision();
		~Colision();

		void TestColision();
		void PushEntity(Entity* entity);
		void SetFuncTest(std::function<bool(Entity* f, Entity* c)> test_function);
	};
}
