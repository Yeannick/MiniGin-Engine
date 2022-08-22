#pragma once

#include "Subject.h"
#include "Observer.h"
#include "BaseComponent.h"
#include "Events.h"

class PlayerController : public Observer, public Subject , public BaseComponent
{
public:
	PlayerController(const std::weak_ptr<GameObject> owner);
	virtual ~PlayerController() override = default;

	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) noexcept = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) noexcept = delete;

	void Update()override {};
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	virtual void OnNotifyAll(EventType eventType, std::shared_ptr<EventArgs> args) override;
private:
	int m_PlayerLives = 3;
};
