#pragma once
#include "BaseComponent.h"
#include "DataTypes.h"
#include "glm/glm.hpp"

class MovementComponent final : public BaseComponent
{
public:
	MovementComponent(const std::weak_ptr<GameObject> owner);
	~MovementComponent() override = default;

	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) noexcept = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) noexcept = delete;

	void Update()override {};
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void Movement(glm::vec3 MovementVector) const;
	void CheckMovement(glm::vec3& velocity, glm::vec3& movementVector)	const;
	
	bool CanMoveInDirection(MovementDirection direction, glm::vec3 velocity ) const; // Check if we can move in direction , so player cannot rotate into wall etc.

};
