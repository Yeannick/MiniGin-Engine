#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Events.h"
class ScoreComponent final : public BaseComponent , public Observer
{

public:
	ScoreComponent(const std::weak_ptr<GameObject> owner);

	~ScoreComponent() override { WriteScore(); }

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

	void Update()override {};
	void Render()override {};
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args) override;
private:
	void WriteScore();
	void ReadScore();

	int m_Score = 0;
	std::vector<int> m_HighScores;
};

