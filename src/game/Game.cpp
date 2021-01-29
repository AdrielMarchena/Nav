#include "Game.h"
#include "Resources.h"
#include "input/Keyboard.h"
#include "audio/SoundDevice.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"



static inline void loadShader()
{
	using namespace engine;
	std::cout << "Loding Adv shader" << std::endl;
	Resources::LoadShader("adv", "src/engine/renderer/shader/Adv.shader");
	std::cout << "Loding bas shader" << std::endl;
	Resources::LoadShader("bas", "src/engine/renderer/shader/Basic.shader");
}
static inline void loadTex()
{
	using namespace engine;
	std::cout << "Loding Frog img" << std::endl;
	Resources::LoadTexture("Frog", "tex/texture.png");
	std::cout << "Loding Nave img" << std::endl;
	Resources::LoadTexture("Nave", "tex/nave.png");
	std::cout << "Loding Test img" << std::endl;
	Resources::LoadTexture("Test", "tex/test.png");
	std::cout << "Loding Ship img" << std::endl;
	Resources::LoadTexture("Ship", "tex/ship.png");
}
static inline void loadSounds()
{
	using namespace engine;
	std::cout << "Loding Shot sound" << std::endl;
	Resources::LoadSound("shot_sound","sounds/shot_sound.ogg");
	std::cout << "Loding Boom sound" << std::endl;
	Resources::LoadSound("boom_sound", "sounds/boom_sound.ogg");
	std::cout << "Loding music sound" << std::endl;
	Resources::LoadSound("music", "sounds/musicOri.ogg");
}

static std::thread LoadAudios;

static inline ImGuiIO& InitImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	return io;
}

static inline bool callback_colisionFunc(Entity* f, Entity* c)
{
	Rect rect1 = f->GetPosition();
	Rect rect2 = c->GetPosition();

	/*if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y) {
		return true;
	}*/
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y) {
		return true;
	}
	return false;
}
Game::Game()
{
}
void Game::IInit()
{
	if (isInit)
		return;

	SoundDevice* mySound = SoundDevice::get();
	LoadAudios = std::thread(loadSounds);
	
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
	loadShader();
	loadTex();

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
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
	
	if (LoadAudios.joinable());
		LoadAudios.join();

	render::Renderer::Init();
	music_speaker = std::make_unique<SoundSource>(0.1f);
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

void Game::IPlayEffect(SoundSource& speaker, ALuint buffer)
{
	speaker.SetGain(effects_global_gain);
	speaker.Play(buffer);
}

void Game::ILoop()
{
	if (!isInit)
	{
		std::cerr << "The game class was not initialized" << std::endl;
		return;
	}

	ImGuiIO& io = InitImGui(window);

	//Play the music
	music_speaker->Loop(true);
	music_speaker->SetGain(0.1f);
	music_speaker->Play(engine::Resources::GetSound("music"));
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	std::cout << "LOOP  STARTING" << std::endl;
	std::cout << "\nArrows Control the Frog\nSpaceBar to Shot\nA to Shot a LOT" << std::endl;
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
	colisor.ClearReserve(entityArray.size());
	sp->SpawnEnemy();
	for (Entity* en : entityArray)
	{
		en->Update(deltaTime);
		if (en->IsSpawned())
			colisor.PushEntity(en);
	}
}

void Game::Loop()
{
	Game::getInstance().ILoop();
}

inline void Game::Draw()
{
	GLCall(glClearColor(0.5f, 0.7f, 0.8f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (Entity* en : entityArray)
		en->Draw(render::Renderer::getInstance());
	
	ImGui::Begin("Game options");
	static float volume = 0.1f;
	ImGui::SliderFloat("Music Volume", &volume, 0.0f,1.0f);
	ImGui::SliderFloat("Effects Volume", &effects_global_gain, 0.0f, 1.0f);
	for (Entity* en : entityArray) 
	{
		en->ImGUiRender();
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	render::Renderer::getInstance().Draw();
	colisor.TestColision();
	music_speaker->SetGain(volume);
}

void Game::Init()
{
	Game::getInstance().IInit();
}

void Game::Clear()
{
	Game::getInstance().IClear();
}

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

void Game::PlayEffect(SoundSource& speaker, ALuint buffer)
{
	Game::getInstance().IPlayEffect(speaker, buffer);
}
