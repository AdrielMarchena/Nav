#include "Game.h"
#include "Resources.h"
#include "input/Keyboard.h"

#include <future>

#include "glm/gtc/matrix_transform.hpp"

static inline void load()
{
	using namespace engine;
	Resources::LoadShader("adv", "src/engine/renderer/shader/Adv.shader");
	Resources::LoadShader("bas", "src/engine/renderer/shader/Basic.shader");
	Resources::LoadTexture("Frog", "tex/texture.png");
	Resources::LoadTexture("Nave", "tex/nave.png");
	Resources::LoadTexture("Test", "tex/test.png");
}
static inline bool callback_colisionFunc(Entity* f, Entity* c)
{
	Rect rect1 = f->GetPosition();
	Rect rect2 = c->GetPosition();

	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y) {
		return true;
	}
	return false;
}
void Game::IInit()
{
	if (isInit)
		return;

	state = GameState::RUNNING;
	isInit = true;

	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Error on glfw initialization" << std::endl;
		state = GameState::END;
		isInit = false;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(screen.w, screen.h, "Nav", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		state = GameState::END;
		isInit = false;
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error on glew initialization" << std::endl;
		state = GameState::END;
		isInit = false;
		return;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//Set resources
	// TODO: Make this multi thread using std::async or something
	load();

	input::Keyboard::Init();

	m_Proj = glm::ortho(0.0f, screen.w, 0.0f, screen.h, -1.0f, 1.0f);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		input::Keyboard::handleInputs(window,key,scancode,action,mods);
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window,int w, int h) { 
		SetScreenSize(w, h);
		SetProjection(glm::mat4(glm::ortho(0.0f, GetScreenSize().w, 0.0f, GetScreenSize().h, -1.0f, 1.0f)));
	});

	sp = new Spawner();

	//Colision function
	colisor.SetFuncTest(callback_colisionFunc);
	render::Renderer::Init();

}

void Game::IClear()
{
	if (Player)
		delete Player;
	if (sp)
		delete sp;
	engine::Resources::Clear();
	render::Renderer::Clear();
	glfwTerminate();
	input::Keyboard::Clear();
	entityArray.clear();
}

bool Game::IIsInit()
{
	return isInit;
}

void Game::ISetGameState(const GameState& newState)
{
	state = newState;
}

void Game::IPushEntity(Entity* entity)
{

	if (!Player)
		if (entity->GetType() == TypeEntity::PLAYER)
			Player = entity;

	entityArray.push_back(entity);
}

void Game::ISetScreenSize(float w, float h)
{
	screen = { w,h };
}

ScreenSize& Game::IGetScreenSize()
{
	return screen;
}

void Game::ISetProjection(glm::mat4 proj)
{
	m_Proj = proj;
}

glm::mat4& Game::IGetProjection()
{
	return m_Proj;
}

void Game::IPushIntoColisor(Entity* entity)
{
	colisor.PushEntity(entity);
}

void Game::ILoop()
{
	if (!isInit)
	{
		std::cerr << "The game class was not initialized" << std::endl;
		return;
	}

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	std::cout << "LOOP  STARTING" << std::endl;
	while (state != GameState::END)
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		HandleInput(deltaTime);
		Update(deltaTime);
		Draw();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

inline void Game::HandleInput(float deltaTime)
{
	if (glfwWindowShouldClose(window))
		state = GameState::END;
	input::Keyboard::clicked(input::Keyboard::ESC_KEY, []() {
		SetGameState(GameState::END);
	});
}

inline void Game::Update(float deltaTime)
{
	for (Entity* en : entityArray)
		en->Update(deltaTime);
	sp->SpawnEnemy();
	colisor.TestColision();
}

void Game::Loop()
{
	Game::getInstance().ILoop();
}

inline void Game::Draw()
{
	GLCall(glClearColor(0.5f, 0.7f, 0.8f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	for (Entity* en : entityArray)
		en->Draw(render::Renderer::getInstance());
	render::Renderer::getInstance().Draw();
}

void Game::Init()
{
	Game::getInstance().IInit();
}

void Game::Clear()
{
	Game::getInstance().IClear();
}

/* Kinda useless */
bool Game::IsInit()
{
	return Game::getInstance().IIsInit();
}

void Game::SetGameState(const GameState& newState)
{
	Game::getInstance().SetGameState(newState);
}

void Game::PushEntity(Entity* entity)
{
	Game::getInstance().IPushEntity(entity);
}

void Game::SetScreenSize(float w, float h)
{
	Game::getInstance().ISetScreenSize(w, h);
}

ScreenSize& Game::GetScreenSize()
{
	return Game::getInstance().IGetScreenSize();
}

glm::mat4& Game::GetProjection()
{
	return Game::getInstance().IGetProjection();
}

void Game::SetProjection(glm::mat4 proj)
{
	return Game::getInstance().ISetProjection(proj);
}

void Game::PushIntoColisor(Entity* entity)
{
	Game::getInstance().IPushIntoColisor(entity);
}
