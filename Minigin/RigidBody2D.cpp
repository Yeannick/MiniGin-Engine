#include "MiniginPCH.h"
#include "RigidBody2D.h"
#include "GameTime.h"
#include "GameObject.h"

RigidBody2D::RigidBody2D(const std::weak_ptr<GameObject>& owner, const glm::vec3& movementspeed):
	BaseComponent(owner),
	m_MovementSpeed(movementspeed)
{
}

void RigidBody2D::FixedUpdate()
{
}

void RigidBody2D::Update()
{
}

void RigidBody2D::LateUpdate()
{
}

void RigidBody2D::Render()
{
}

void RigidBody2D::Movement(const glm::vec3 moveVec)
{
	
	m_Velocity = moveVec * GameTime::GetInstance().GetDeltaTime() * m_MovementSpeed;

	glm::vec3 position = m_Owner.lock()->GetTransform().GetPosition();
	//m_Velocity.y *= -1;
	position += m_Velocity;

	m_Owner.lock()->SetPosition(position.x,position.y,position.z);
}
