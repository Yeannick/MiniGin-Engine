#include "GameManager.h"
#include "Events.h"
#include "SceneManager.h"
#include "EnemyController.h"
#include "PlayerControllerComponent.h"
#include "Scene.h"

void GameManager::LateUpdate()
{
	if (IsGameOver)
	{
		
		SceneManager::GetInstance().LoadScene("HighScore");
		IsGameOver = false;
	}
	if (nextLevel)
	{
		NextLevel();
	}
}

void GameManager::OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args)
{
	
	switch (event)
	{
	case EventType::NEXTLEVEL :
		nextLevel = true;
		
		break;
	case EventType::GAMEOVER:
		IsGameOver = true;
		break;
	default:
		break;
	}
}

void GameManager::NextLevel()
{
	switch (m_ActiveLevel)
	{
	case GameManager::Levels::LEVEL1:
		
		SceneManager::GetInstance().LoadScene("Level02");
		m_ActiveLevel = Levels::LEVEL2;
		break;
	case GameManager::Levels::LEVEL2:
		SceneManager::GetInstance().LoadScene("Level03");
		m_ActiveLevel = Levels::LEVEL3;
		break;
	case GameManager::Levels::LEVEL3:
		SceneManager::GetInstance().LoadScene("Level01");
		m_ActiveLevel = Levels::LEVEL1;
		break;
	}
	const auto& scene{ SceneManager::GetInstance().GetScene() };
	const auto EnemyControllers = scene.GetGameObjectsByTag("Enemy");
	const auto controllers = scene.GetGameObjectsByTag("Player");
	for (const auto& controller : controllers)
	{
		controller->GetComponent<TankComponent>().lock()->Teleport();
	}
	for (const auto& controller : EnemyControllers)
	{
		for (size_t i = 0; i < controllers.size(); i++)
		{
			controller->GetComponent<EnemyController>().lock()->AddTarget(controllers[i].get());
		}
		
	}
}
