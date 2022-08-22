#include "PlayerControllerComponent.h"
#include "TankComponent.h"
#include "SceneManager.h"
#include"Scene.h"
PlayerController::PlayerController(const std::weak_ptr<GameObject> owner):BaseComponent(owner)
{
}

void PlayerController::OnNotifyAll(EventType eventType, std::shared_ptr<EventArgs> args)
{
	if (EventType::DIED == eventType || m_PlayerLives > 0)
	{
		
		m_PlayerLives--;
		if (m_PlayerLives <= 0)
		{
			NotifyAll(EventType::GAMEOVER, std::make_shared<GameObjectArgs>(m_Owner.lock().get()));
			m_Owner.lock()->MarkForDestruction();
			return;
		}
		auto vecEnemy = SceneManager::GetInstance().GetScene().GetGameObjectsByTag("Enemy");
		if (vecEnemy.empty())
		{
			NotifyAll(EventType::NEXTLEVEL, std::make_shared<GameObjectArgs>(m_Owner.lock().get()));
		}
		
		
	}
}
