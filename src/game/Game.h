#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>

#include "glm/glm.hpp"

#include "Entity.h"
#include "Spawner.h"

#include "Colision.h"

#define WINDOW_WIDTH 375.0f
#define WINDOW_HEIGHT 800.0f

enum class GameState : uint8_t
{
	INVALID,
	RUNNING,
	PAUSE,
	GAME_OVER,
	END
};

struct ScreenSize
{
	float w, h;

	ScreenSize(float W = WINDOW_WIDTH, float H = WINDOW_HEIGHT)
		:w(W), h(H)
	{
	}
};

/*
	Singleton
*/
class Game
{
private:
	//Singleton stuff
	Game(){}
	Game(Game const&) = delete;
	void operator = (Game const&) = delete;
public:
	//Singleton stuff
	static Game& getInstance() { static Game instace; return instace; }
	
	//Game things
	static void Init();
	static void Clear();

	static bool IsInit();
	static void SetGameState(const GameState& newState);
	static void PushEntity(Entity* entity);
	static void SetScreenSize(float w, float h);
	static ScreenSize& GetScreenSize();
	static glm::mat4& GetProjection();
	static void SetProjection(glm::mat4 proj);
	static void PushIntoColisor(Entity* entity);

	/* Start Game loop */
	static void Loop();
	
private:
	//Game things
	void IInit();
	void IClear();

	bool IIsInit();
	void ISetGameState(const GameState& newState);
	void IPushEntity(Entity* entity);
	void ISetScreenSize(float w, float h);
	ScreenSize& IGetScreenSize();
	void ISetProjection(glm::mat4 proj);
	glm::mat4& IGetProjection();
	void IPushIntoColisor(Entity* entity);
	void Reset();
	/* Start Game loop */
	void ILoop();
	GameState state;
	bool isInit;
	ScreenSize screen;

	engine::Colision colisor;

	glm::mat4 m_Proj;
	
	Entity* Player;
	Spawner* sp;

	GLFWwindow* window;

	std::vector<Entity*> entityArray;

	inline void HandleInput(float deltaTime);
	inline void Update(float deltaTime);
	inline void Draw();
};