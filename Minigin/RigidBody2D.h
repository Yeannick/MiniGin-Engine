#pragma once
#include "BaseComponent.h"

class RigidBody2D : public BaseComponent
{
public :
	RigidBody2D(const std::weak_ptr<GameObject>& owner, const glm::vec3& movementspeed);
	~RigidBody2D()override = default;

	RigidBody2D(const RigidBody2D& other) = delete;
	RigidBody2D(RigidBody2D&& other) noexcept = delete;
	RigidBody2D& operator=(const RigidBody2D& other) = delete;
	RigidBody2D& operator=(RigidBody2D&& other) noexcept = delete;

	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Movement(const glm::vec3 moveVec);

	glm::vec3 GetMovementSpeed() const { return m_MovementSpeed; }
	glm::vec3 GetVelocity() const { return m_Velocity; }

private:
	glm::vec3 m_Velocity = {0,0,0};
	glm::vec3 m_MovementSpeed = {0,0,0};
};