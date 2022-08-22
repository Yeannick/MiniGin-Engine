#pragma once
#include "BaseComponent.h"
#include <vector>
#include "TextComponent.h"
#include "ResourceManager.h"
class HighScore final : public BaseComponent
{
public:
	HighScore(const std::weak_ptr<GameObject> owner) : BaseComponent(owner)
	{
		m_HighScores.resize(10);
		ReadHighScoreFile();
	
	}
	~HighScore() override = default;

	HighScore(const HighScore& other) = delete;
	HighScore(HighScore&& other) noexcept = delete;
	HighScore& operator=(const HighScore& other) = delete;
	HighScore& operator=(HighScore&& other) noexcept = delete;


	void Update()override;
	void Render()override;
	void FixedUpdate()override {};
	void LateUpdate()override {};
private:
	void ReadHighScoreFile();
	std::vector<int> m_HighScores;

	float m_HighScoreSceneDuration = 3.f;
	float m_TimePassed = 0.f;
};

