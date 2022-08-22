#include "HighScore.h"
#include "GameTime.h"
#include <fstream>

#include "GameObject.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Scene.h"
void HighScore::Update()
{
	m_TimePassed += GameTime::GetInstance().GetDeltaTime();

	if (m_TimePassed >= m_HighScoreSceneDuration)
	{
		SceneManager::GetInstance().GetScene().Remove();
		//SceneManager::GetInstance().GetScene().RemoveDefaults();
		SceneManager::GetInstance().LoadScene("MainMenu");
		
		
	}
}

void HighScore::Render()
{

	
	auto color = SDL_Color{ 255,255,255,255 };

	const size_t len{ m_HighScores.size() };
	
	for (size_t i = 0; i < len; ++i)
	{
		const std::string line{ std::to_string(i + 1) + ": " + std::to_string(m_HighScores[i]) };
		SDL_Rect DestRect{ 200,(480 / len) * i, 100 , 48 };
		Renderer::GetInstance().RenderText(line,DestRect,"Lingua.otf",color);
	}
}

void HighScore::ReadHighScoreFile()
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
