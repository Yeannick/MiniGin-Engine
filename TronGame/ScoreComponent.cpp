#include "ScoreComponent.h"
#include "TankComponent.h"
#include "TextComponent.h"
#include <algorithm>
#include <fstream>

ScoreComponent::ScoreComponent(const std::weak_ptr<GameObject> owner):BaseComponent(owner)
{
	m_HighScores.resize(10);
	ReadScore();
}

void ScoreComponent::OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args)
{
	const auto gameobjectArgs{ dynamic_cast<GameObjectArgs*>(args.get()) };
	auto go = gameobjectArgs->gameobject;
	const auto tank = go->GetComponent<TankComponent>().lock().get();
	switch (event)
	{
	case EventType::KILL:
	
		if (tank)
		{
			m_Score += tank->GetValue();
			const auto textcomp = m_Owner.lock()->GetComponent<TextComponent>().lock();
			if (textcomp)
			{
				textcomp->SetText(std::to_string(m_Score));
			}
		}
		break;
	case EventType::GAMEOVER:
		WriteScore();
		m_Score = 0;

		const auto textcomp = m_Owner.lock()->GetComponent<TextComponent>().lock();
		if (textcomp)
		{
			textcomp->SetText(std::to_string(m_Score));
		}
		break;
	
	}
}

void ScoreComponent::WriteScore()
{
	std::sort(m_HighScores.begin(),m_HighScores.end(), std::greater <int>());
	// add new score to list if it is a new top 10 
	for (int& score : m_HighScores)
	{
		if (score < m_Score)
		{
			const int tempScore{ score };
			score = m_Score;
			m_Score = tempScore;
		}
	}
	// write it away in file
	if (std::ofstream stream{ "../Data/HighScore.hsf" })
	{
		for (size_t i = 0; i < m_HighScores.size(); ++i)
		{
			stream << "-" << i << "- " << m_HighScores[i] << std::endl;
		}
		stream.close();
	}
}

void ScoreComponent::ReadScore()
{
	std::ifstream stream{ "../Data/HighScore.hsf", std::ios::in };
	if (stream)
	{
		std::string line;
		while (std::getline(stream, line))
		{
			const int idx = std::stoi(line.substr(line.find('-') + 1));
			line = line.substr(line.find('-') + 1);
			m_HighScores[idx] = std::stoi(line);
		}
		stream.close();
	}

	stream.close();
}
