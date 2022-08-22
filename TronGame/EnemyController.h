#pragma once
#include "PlayerControllerComponent.h"
#include "TankComponent.h"
#include <algorithm>
#include "SceneManager.h"
#include "Scene.h"
class EnemyController final : public PlayerController
{
public:
	EnemyController(const std::weak_ptr<GameObject> owner) : PlayerController(owner)
	{
		
		const auto controllers = SceneManager::GetInstance().GetScene().GetGameObjectsByTag("Player");
		for (size_t i = 0; i < controllers.size(); i++)
		{
			AddTarget(controllers[i].get());
		}
	
	}
	~EnemyController() override = default;

	EnemyController(const EnemyController& other) = delete;
	EnemyController(EnemyController&& other) noexcept = delete;
	EnemyController& operator=(const EnemyController& other) = delete;
	EnemyController& operator=(EnemyController&& other) noexcept = delete;

	void Update()override ;
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void OnNotifyAll(EventType eventType, std::shared_ptr<EventArgs> args) override;

	void AddTarget(GameObject* pTarget);
	void RemoveTarget(GameObject* pTarget);
	void SetTargets(const std::vector<GameObject*>& pTargets);

private:
	void CalculateMovement() const;
	void FindTarget();
	void CalculateAttack();
	float CalculateAngle(glm::vec3 angle);
	float CalculateMagnitude(glm::vec3 vector);
	float DegreesToRadians(float degrees );
	float RadiansToDegrees(float radians);


	std::vector<GameObject*> m_pTargets;
	GameObject* m_pCurrentTarget = nullptr;
	const float m_FireRate = 0.5f;
	float m_CurrentRate = m_FireRate;
};

