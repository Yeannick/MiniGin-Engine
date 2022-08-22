#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "SoundServiceLocator.h"
#include "Scene.h"
#include "JsonFileReader.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Prefabs.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "SkipLevelButton.h"
#include "GameModeButton.h"
#include "HighScore.h"
#include "UiManager.h"

void MainMenu(Scene& scene)
{
	const auto SoloButton{ std::make_shared<GameObject>("button")};
	SoloButton->AddComponent<GameModeButton>(std::make_shared<GameModeButton>(SoloButton, SDL_Rect{ 0,0,466,105 }, SDL_Rect{ 225,50,175,75 }, "Button.png" , "SOLO"));
	scene.Add(SoloButton);

	const auto CoopButton{ std::make_shared<GameObject>("button") };
	CoopButton->AddComponent<GameModeButton>(std::make_shared<GameModeButton>(CoopButton, SDL_Rect{ 0,0,466,105 }, SDL_Rect{ 225,200,175,75 }, "Button.png", "COOP"));
	scene.Add(CoopButton);

	const auto VersusButton{ std::make_shared<GameObject>("button") };
	VersusButton->AddComponent<GameModeButton>(std::make_shared<GameModeButton>(VersusButton, SDL_Rect{ 0,0,466,105 }, SDL_Rect{ 225,350,175,75 }, "Button.png", "VERSUS"));
	scene.Add(VersusButton);
}
void HighScoreScene(Scene& scene)
{
	UIManager::GetInstance().RemoveButtons();
	const auto highscore = std::make_shared<GameObject>();
	highscore->AddComponent<HighScore>(std::make_shared<HighScore>(highscore));
	scene.Add(highscore);
}
void LoadLevel01(Scene& scene)
{
	
	JsonFileReader::GetInstance().ReadFile(scene, "Level01.json");
	auto bground = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto color = SDL_Color{ 0,255,0,255 };
	bground->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(bground,font,color));
	bground->SetPosition(550, 0, 0.2f);
	
	auto players = scene.GetGameObjectsByTag("Player");
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->GetComponent<TankComponent>().lock()->Teleport();
	}
	
	scene.Add(bground);
	
	scene.Add(BlueTankEnemyPrefab(scene));
	auto enemyplayers = scene.GetGameObjectsByTag("Enemy");
	for (size_t i = 0; i < players.size(); i++)
	{
		enemyplayers[i]->GetComponent<TankComponent>().lock()->Teleport();
	}
}
void LoadLevel02(Scene& scene)
{
	JsonFileReader::GetInstance().ReadFile(scene, "Level02.json");
	auto bground = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto color = SDL_Color{ 0,255,0,255 };
	bground->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(bground, font, color));
	bground->SetPosition(550, 0, 0.2f);

	auto players = scene.GetGameObjectsByTag("Player");
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->GetComponent<TankComponent>().lock()->Teleport();
	}
	scene.Add(BlueTankEnemyPrefab(scene));
	scene.Add(BlueTankEnemyPrefab(scene));
	scene.Add(bground);
}
void LoadLevel03(Scene& scene)
{
	JsonFileReader::GetInstance().ReadFile(scene, "Level03.json");
	auto bground = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto color = SDL_Color{ 0,255,0,255 };
	bground->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(bground, font, color));
	bground->SetPosition(550, 0, 0.2f);
	auto players = scene.GetGameObjectsByTag("Player");
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->GetComponent<TankComponent>().lock()->Teleport();
	}
	scene.Add(BlueTankEnemyPrefab(scene));
	scene.Add(BlueTankEnemyPrefab(scene));
	scene.Add(BlueTankEnemyPrefab(scene));
	scene.Add(bground);
}

void Solo(Scene& scene)
{
	
	const auto gameManager = std::make_shared<GameObject>("GameManager") ;
	gameManager->AddComponent<GameManager>(std::make_shared<GameManager>(gameManager));
	scene.AddDefault(gameManager);

	scene.AddDefault(PlayerPrefab(scene));

	const auto skipButton{ std::make_shared<GameObject>() };
	skipButton->AddComponent<SkipLevelButton>(std::make_shared<SkipLevelButton>( skipButton, SDL_Rect{ 0,0,600,200 }, SDL_Rect{ 500,300,100,30 }, "Button.png"));
	scene.AddDefault(skipButton);
	
	LoadLevel01(scene);
	
}
void Coop(Scene& scene)
{
	
	const auto gameManager = std::make_shared<GameObject>("GameManager");
	gameManager->AddComponent<GameManager>(std::make_shared<GameManager>(gameManager));
	scene.AddDefault(gameManager);
	scene.AddDefault(PlayerPrefab(scene));
	/*const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);*/
	const auto skipButton{ std::make_shared<GameObject>() };
	skipButton->AddComponent<SkipLevelButton>(std::make_shared<SkipLevelButton>(skipButton, SDL_Rect{ 0,0,600,200 }, SDL_Rect{ 500,300,100,30 }, "Button.png"));
	scene.AddDefault(skipButton);

	//const auto player2{ GreenTankPrefab(scene) };
	scene.AddDefault(GreenTankPlayerPrefab(scene));
	LoadLevel01(scene);
}
void Versus(Scene& scene)
{
	
	const auto gameManager = std::make_shared<GameObject>("GameManager");
	gameManager->AddComponent<GameManager>(std::make_shared<GameManager>(gameManager));
	scene.AddDefault(gameManager);

	/*const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);*/
	scene.AddDefault(PlayerPrefab(scene));
	const auto skipButton{ std::make_shared<GameObject>() };
	skipButton->AddComponent<SkipLevelButton>(std::make_shared<SkipLevelButton>(skipButton, SDL_Rect{ 0,0,600,200 }, SDL_Rect{ 500,300,100,30 }, "Button.png"));
	scene.AddDefault(skipButton);
	scene.AddDefault(BlueTankPlayerPrefab(scene));
	//const auto player2{ BluePlayerTankPrefab(scene) };
	//scene.AddDefault(player2);
	LoadLevel01(scene);
}
int main(int, char* []) {
	Minigin engine;
	engine.Initialize();
	SoundServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	SceneManager::GetInstance().SetSpawnLevelFunc(MainMenu, "MainMenu");
	SceneManager::GetInstance().SetSpawnLevelFunc(Solo, "SOLO");
	SceneManager::GetInstance().SetSpawnLevelFunc(Coop, "COOP");
	SceneManager::GetInstance().SetSpawnLevelFunc(Versus, "VERSUS");
	SceneManager::GetInstance().SetSpawnLevelFunc(LoadLevel01, "Level01");
	SceneManager::GetInstance().SetSpawnLevelFunc(LoadLevel02, "Level02");
	SceneManager::GetInstance().SetSpawnLevelFunc(LoadLevel03, "Level03");
	SceneManager::GetInstance().SetSpawnLevelFunc(HighScoreScene, "HighScore");
	SceneManager::GetInstance().LoadScene("MainMenu");

	//LoadLevel01(level1);
	engine.Run();

	SoundServiceLocator::FreeSoundSystem();
	return 0;
}