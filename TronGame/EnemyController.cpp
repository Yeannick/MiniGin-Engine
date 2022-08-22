#include "EnemyController.h"
#include "GameTime.h"
#include "PhysicsManager.h"
#include "MovementComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void EnemyController::Update()
{
	if (m_pTargets.empty())
	{
		// nothing to do 
		return;
	}

	FindTarget();
	CalculateAttack();
	CalculateMovement();

}

void EnemyController::OnNotifyAll(EventType eventType, std::shared_ptr<EventArgs> args)
{
	if (EventType::DIED == eventType)
	{
		//m_Owner.lock()->GetChild(0)->MarkForDestruction();
		
		PhysicsManager::GetInstance().RemoveBoxCollider2D(m_Owner.lock()->GetComponent<BoxCollider2D>().lock());
		m_Owner.lock()->MarkForDestruction();
		m_Owner.lock()->RemoveChild(0);

		auto vecEnemy = SceneManager::GetInstance().GetScene().GetGameObjectsByTag("Enemy");
		if (vecEnemy.size() <= 1)
		{
			NotifyAll(EventType::NEXTLEVEL, std::make_shared<GameObjectArgs>(m_Owner.lock().get()));
		}
		return;

	}
}

void EnemyController::AddTarget(GameObject* pTarget)
{
	m_pTargets.push_back(pTarget);
}

void EnemyController::RemoveTarget(GameObject* pTarget)
{
	m_pTargets.erase(std::remove(m_pTargets.begin(),m_pTargets.end(), pTarget));
}

void EnemyController::SetTargets(const std::vector<GameObject*>& pTargets)
{
	m_pTargets = pTargets;
}

void EnemyController::CalculateMovement() const
{
	glm::vec3 movementVector;
	glm::vec3 Direction = m_pCurrentTarget->GetTransform().GetPosition() - m_Owner.lock()->GetTransform().GetPosition();
	if (Direction.x < 0)
	{
		movementVector.x = -1;
	}
	else if (Direction.x > 0)
	{
		movementVector.x = 1;
	}
	if (Direction.y < 0)
	{
		movementVector.y = -1;
	}
	else if (Direction.y > 0)
	{
		movementVector.y = 1;
	}
	m_Owner.lock()->GetComponent<MovementComponent>().lock()->Movement(movementVector);
}

void EnemyController::FindTarget()
{
	const auto position = m_Owner.lock()->GetTransform().GetPosition();
	m_pCurrentTarget = m_pTargets.front();
	if (m_pCurrentTarget)
	{
		int distance = static_cast<int>(CalculateMagnitude(m_pCurrentTarget->GetTransform().GetPosition() - position));
		for (const auto& pTarget : m_pTargets)
		{
			if (pTarget == m_pCurrentTarget)
				continue;

			const int distanceEnemy = static_cast<int>(CalculateMagnitude(pTarget->GetTransform().GetPosition() - position));
			if (distanceEnemy < distance)
			{
				m_pCurrentTarget = pTarget;
				distance = distanceEnemy;
			}
		}
	}
}

void EnemyController::CalculateAttack()
{
	const auto tankComp{ m_Owner.lock()->GetComponent<TankComponent>() };

	const glm::vec3 DiffVec = m_pCurrentTarget->GetTransform().GetPosition() - m_Owner.lock()->GetTransform().GetPosition();
	const float angle = CalculateAngle(DiffVec) - tankComp.lock()->GetAngle();
	
	tankComp.lock()->Rotate(angle > 0);

	if (m_CurrentRate < m_FireRate)
		m_CurrentRate += GameTime::GetInstance().GetDeltaTime();
	else
	{
		const glm::vec3 dir{ cos(DegreesToRadians(tankComp.lock()->GetAngle())),sin(DegreesToRadians(tankComp.lock()->GetAngle())),0};
		float distance = glm::length(DiffVec);
		if (distance < 60.f)
		{
			tankComp.lock()->Attack();
			m_CurrentRate -= m_FireRate;
		}
	}
}

float EnemyController::CalculateAngle(glm::vec3 angle)
{
	const float M = CalculateMagnitude(angle);
	const float V = CalculateMagnitude(glm::vec3{1,0,0});

	return RadiansToDegrees(acos(glm::dot(angle, glm::vec3{1,0,0})/ (M*V)));
}

float EnemyController::CalculateMagnitude(glm::vec3 vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float EnemyController::DegreesToRadians(float degrees)
{
	return degrees * M_PI / 180.f;
}

float EnemyController::RadiansToDegrees(float radians)
{
	return radians * 180.f/ M_PI;
}
