#include "TankComponent.h"
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "PhysicsManager.h"
#include "SoundServiceLocator.h"
#include "GameTime.h"
#include "Events.h"
#include "Prefabs.h"
#include <cmath>
#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

TankComponent::TankComponent(const std::weak_ptr<GameObject> owner, int value, SDL_Rect playableRect):
	BaseComponent(owner),
	m_Value(value),
	m_PlayableRect(playableRect)
{
	
	//spawn at random loc
	Teleport();
}

void TankComponent::Update()
{

}

void TankComponent::Rotate(bool cw)
{
	if (cw)
	{
		
		m_Angle += m_RotSpeed * GameTime::GetInstance().GetDeltaTime();
		
	}
	else
	{
		m_Angle -= m_RotSpeed * GameTime::GetInstance().GetDeltaTime();
		
	}

	if (m_Angle >= 360)
	{
		float tempAngle = m_Angle ;
		while (tempAngle - 360 >= 0)
		{
			tempAngle -= 360;
		}
		m_Angle = tempAngle;
	}
	if (m_Angle < 0)
	{
		float tempAngle = m_Angle ;
		while (tempAngle < 0)
		{
			tempAngle += 360;
		}
		m_Angle = tempAngle;
	}

	if (m_Owner.lock()->GetChildCount() != 0)
	{
		m_Owner.lock()->GetChild("TankTop")->SetRotation(-m_Angle);
	}
	
}

void TankComponent::Attack() const
{
	SoundServiceLocator::GetSoundSystem().QueueSound("Attack.wav",0,50,false);

	float angleRadians = (m_Angle* M_PI) / 180.f;
	// Create Bullet
	float cosRadians = cos(angleRadians);
	float sinRadians = sin(angleRadians);
	const auto bullet = BulletPrefab(m_Owner.lock().get(), glm::vec3{cosRadians,-sinRadians,0 });
	SceneManager::GetInstance().GetScene().Add(bullet);
	const auto position = m_Owner.lock()->GetTransform().GetPosition() + glm::vec3{ 6.5f,6.5f,0 };
	// Shoot bullet 
	bullet->SetPosition(position.x, position.y);
	
}

void TankComponent::TakeDamage() 
{
	NotifyAll(EventType::LOSTHEALTH, std::make_shared<GameObjectArgs>(m_Owner.lock().get()) );
}


void TankComponent::Teleport() const
{
	srand(static_cast<unsigned>(time(nullptr)));
	std::shared_ptr<BoxCollider2D> Collider = m_Owner.lock()->GetComponent<BoxCollider2D>().lock();
	
	glm::vec2 randomPosition = { rand() % m_PlayableRect.w , rand() % m_PlayableRect.h };
	randomPosition = CheckTeleportPos(randomPosition);
	m_Owner.lock()->SetPosition(randomPosition.x, randomPosition.y);
}

glm::vec2 TankComponent::CheckTeleportPos(glm::vec2 pos) const
{
	std::shared_ptr<BoxCollider2D> Collider = m_Owner.lock()->GetComponent<BoxCollider2D>().lock();
	auto oldCollider = Collider->GetBoxCollider();
	auto tempColl = SDL_Rect{ int(pos.x) , int(pos.y) , Collider->GetBoxCollider().w,Collider->GetBoxCollider().h };
	Collider->SetBoxCollider(tempColl);
	while (PhysicsManager::GetInstance().IsOverlapping(Collider, true))
	{
		if (pos.x > m_PlayableRect.x + m_PlayableRect.w)
		{
			pos.x -= 1;
		}
		if (pos.x < m_PlayableRect.x)
		{
			pos.x += 1;
		}
		if (pos.y > m_PlayableRect.y + m_PlayableRect.h)
		{
			pos.y -= 1;
		}
		if (pos.y < m_PlayableRect.y)
		{
			pos.y += 1;
		}
		pos = { rand() % m_PlayableRect.w, rand() % m_PlayableRect.h };
	
		auto tempColl = SDL_Rect{ int(pos.x) , int(pos.y) , Collider->GetBoxCollider().w,Collider->GetBoxCollider().h };
		Collider->SetBoxCollider(tempColl);
	}
	return pos;
}


