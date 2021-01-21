#include <iostream>

#include "renderer/OpenGL/opl.h"
#include "renderer/Renderer.h"

#include "game/Game.h"
#include "Resources.h"
#include "game/Player.h"

#include "game/Utils/RandomList.h"

int main(int argc, char* argv[])
{
	using namespace engine;
		
	Game &game = Game::getInstance();
	game.Init();

	Player* player = new Player();

	game.PushEntity(player);
	game.PushIntoColisor(player);
	game.Loop();

	game.Clear();

	return 0;
}