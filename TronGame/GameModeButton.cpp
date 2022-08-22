#include "GameModeButton.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "UiManager.h"
void GameModeButton::Render()
{
	UIButton::Render();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12).get();
	const auto offset{ m_DstRect.w / 10 };
	const SDL_Rect offsetRect{ m_DstRect.x + offset,m_DstRect.y + offset,m_DstRect.w - 2 * offset, m_DstRect.h - 2 * offset };
	Renderer::GetInstance().RenderText(m_LevelName, offsetRect, "Lingua.otf", color);
	
}

void GameModeButton::OnButtonUp()
{
	SceneManager::GetInstance().LoadScene(m_LevelName);
	UIManager::GetInstance().RemoveButtons();
}
