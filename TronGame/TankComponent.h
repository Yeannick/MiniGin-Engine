#pragma once

#include "BaseComponent.h"
#include "Subject.h"
#include "SDL.h"
#include "glm/glm.hpp"

class TankComponent : public BaseComponent , public Subject
{
public:
	TankComponent(const std::weak_ptr<GameObject> owner, int value, SDL_Rect playableRect);
	~TankComponent() override = default;

	TankComponent(const TankComponent& other) = delete;
	TankComponent(TankComponent&& other) noexcept = delete;
	TankComponent& operator=(const TankComponent& other) = delete;
	TankComponent& operator=(TankComponent&& other) noexcept = delete;

	void Update()override;
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void Rotate(bool cw);
	void Attack()const;
	void TakeDamage();

	

	void Teleport()const;
	glm::vec2 CheckTeleportPos(glm::vec2 pos) const;

	float GetAngle()const { return m_Angle; }
	int GetValue()const { return m_Value; }


private:
	
	float m_Angle = 0.f;
	float m_RotSpeed = 50.f;

	SDL_Rect m_PlayableRect;
	int m_Value;
};

