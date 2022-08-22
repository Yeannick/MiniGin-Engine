#pragma once
#include "Command.h"
#include "TankComponent.h"
#include "MovementComponent.h"
#include <iostream>
class AttackCommand final : public Command
{
public:
	AttackCommand(GameObject* go) :Command(go) {}
	~AttackCommand() override = default;

	AttackCommand(const AttackCommand& other) = delete;
	AttackCommand(AttackCommand&& other) noexcept = delete;
	AttackCommand& operator=(const AttackCommand& other) = delete;
	AttackCommand& operator=(AttackCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetOwningGameObject()->GetComponent<TankComponent>().lock()->Attack();
		//std::cout << "attack\n";
	}
};

class MovementCommand final : public Command
{
public:
	MovementCommand(GameObject* go, const glm::vec3& moveVec) :Command(go), m_MovementVector(moveVec) {}
	~MovementCommand() override = default;

	MovementCommand(const MovementCommand& other) = delete;
	MovementCommand(MovementCommand&& other) noexcept = delete;
	MovementCommand& operator=(const MovementCommand& other) = delete;
	MovementCommand& operator=(MovementCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetOwningGameObject()->GetComponent<MovementComponent>().lock()->Movement(m_MovementVector);
		//std::cout << "Move\n";

	}
private:
	glm::vec3 m_MovementVector;
};

class RotateCommand final : public Command
{
public:
	RotateCommand(GameObject* gameObject, bool clockwise = false) :Command(gameObject), m_IsClockWiseRotation(clockwise) {}
	~RotateCommand() override = default;

	RotateCommand(const RotateCommand& other) = delete;
	RotateCommand(RotateCommand&& other) noexcept = delete;
	RotateCommand& operator=(const RotateCommand& other) = delete;
	RotateCommand& operator=(RotateCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetOwningGameObject()->GetComponent<TankComponent>().lock()->Rotate(m_IsClockWiseRotation);
		

	}
private:
	bool m_IsClockWiseRotation{ false };
};