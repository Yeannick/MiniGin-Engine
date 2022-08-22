#pragma once

#include "BaseComponent.h"
#include "glm/glm.hpp"
#include "BoxCollider2D.h"

class BulletComponent final : public BaseComponent
{
public:
	BulletComponent(const std::weak_ptr<GameObject> owner, GameObject* pParentGO, const glm::vec3& direction);
	~BulletComponent() override = default;

	BulletComponent(const BulletComponent& other) = delete;
	BulletComponent(BulletComponent&& other) noexcept = delete;
	BulletComponent& operator=(const BulletComponent& other) = delete;
	BulletComponent& operator=(BulletComponent&& other) noexcept = delete;

	void Update()override;
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override ;

	bool IsDestroyed() const;
	void Bounce(const BoxCollider2D* overlappingBox);
	void CheckOverlap();

private:

	GameObject* m_pParent = nullptr; // GameObject that actually fires the bullet. the owner in the constructor is de GO that owns the bulletComponent so the actual Bullet
	const unsigned int m_MaxBounces = 5;
	unsigned int m_AmountOfBounces = 0;

	bool m_IsDestroyed = false;
	glm::vec3 m_Direction;


	// only needed to check overlap isnt same as previous frame . Dirty solution #TODO find better solution

	BoxCollider2D* m_pPreviousCollision = nullptr;
};