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
	void Colision::ClearReserve(unsigned int qtd)
	{
		entitys.clear();
		entitys.reserve(qtd);
	}
	/* Iterate in Entity List and call the function provided to the class */
	void Colision::TestColision()
	{
		for (auto ent : entitys)
		{
			//if (ent->IsSpawned())
			for (auto entT : entitys)
			{
				/*
				//Don't test Colision with yourself or with somethin that is not in screen
				//if (!entT->IsSpawned() || !ent->IsSpawned() || ent == entT)
					//continue;
				*/
				if(ent != entT)
				if (test_function(ent, entT))
				{
					entT->ColisionCallBack(ent);
	 				ent->ColisionCallBack(entT);
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

