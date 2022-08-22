#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Subject.h"
class HealthComponent final : public BaseComponent , public Observer , public Subject
{
public:
	HealthComponent(const std::weak_ptr<GameObject> owner, int health) : BaseComponent(owner), m_Health(health)
	{}
	~HealthComponent() override = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Update()override {};
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args) override;
private:
	int m_Health;
};

