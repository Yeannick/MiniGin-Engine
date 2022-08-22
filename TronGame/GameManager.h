#pragma once
#include "BaseComponent.h"
#include "Observer.h"
class GameManager final : public BaseComponent , public Observer
{
public:
	enum class Levels
	{
		LEVEL1,
		LEVEL2,
		LEVEL3
	};

	GameManager(const std::weak_ptr<GameObject> owner) : BaseComponent(owner)
	{
	}
	~GameManager() override = default;

	GameManager(const GameManager & other) = delete;
	GameManager(GameManager && other) noexcept = delete;
	GameManager& operator=(const GameManager & other) = delete;
	GameManager& operator=(GameManager && other) noexcept = delete;

	void Update()override {};
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override ;

	void OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args) override;

private:
	void NextLevel();
	bool IsGameOver = false;
	bool nextLevel = false;
	Levels m_ActiveLevel = Levels::LEVEL1;

};

