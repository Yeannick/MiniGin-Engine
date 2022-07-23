#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "GameTime.h"
#include <chrono>


using namespace std;
using namespace std::chrono;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	

	auto bground = std::make_shared<GameObject>();

	bground->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(bground));
	bground->SetPosition(0, 0, 0.2f);
	auto sprite = bground->GetComponent<SpriteComponent>();
	sprite.lock()->SetTexture("background.jpg");
	sprite.lock()->SetSpriteRect(0,0,640,480);
	scene.Add(bground);
	/*auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/
	auto go = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto color = SDL_Color{ 255,255,255,255 };
	go->AddComponent<TextComponent>(std::make_shared<TextComponent>(go, "Programming 4 Assignment", font, color));

	scene.Add(go);
}

void Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			float dt = std::chrono::duration<float>(currentTime - lastTime).count();
			// Set DeltaTime in GameTime
			GameTime::GetInstance().SetDeltaTime(dt);

			lastTime = currentTime;
			lag += dt;


			doContinue = input.ProcessInput();

			while (lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerFrame;
			}
			sceneManager.Update();
			sceneManager.LateUpdate();

			renderer.Render();

			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			std::this_thread::sleep_for(sleepTime);


		}
	}

	Cleanup();
}
