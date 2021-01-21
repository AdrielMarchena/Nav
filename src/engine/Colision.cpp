#include "Colision.h"
namespace engine
{
	Colision::Colision(std::vector<Entity*> entitys, std::function<bool(Entity* f, Entity* c)> test_function)
		:entitys(entitys),test_function(test_function)
	{
	}

	Colision::Colision()
	{
	}

	Colision::~Colision()
	{
		entitys.clear();
	}
	/* Iterate in Entity List and call the function provided to the class */
	void Colision::TestColision()
	{
		for (auto ent : entitys)
		{
			for (auto entT : entitys)
			{
				// Don't test Colision with yourself or with somethin that is not in screen
				if (!ent->IsSpawned() || !entT->IsSpawned() || ent == entT)
					continue;
				if (test_function(ent, entT))
				{
	 				ent->ColisionCallBack(entT);
					entT->ColisionCallBack(ent);
				}
			}
		}
	}

	void Colision::PushEntity(Entity* entity)
	{
		entitys.push_back(entity);
	}
	void Colision::SetFuncTest(std::function<bool(Entity* f, Entity* c)> test_function)
	{
		this->test_function = test_function;
	}
}

