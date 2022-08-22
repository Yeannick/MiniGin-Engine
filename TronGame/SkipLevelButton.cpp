#include "SkipLevelButton.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameManager.h"
#include "Events.h"
#include "Renderer.h"
void SkipLevelButton::Render()
{
	UIButton::Render();
	const auto offset{ m_DstRect.w / 10 };
	const SDL_Rect offsetRect{ m_DstRect.x + offset,m_DstRect.y + offset,m_DstRect.w - 2 * offset, m_DstRect.h - 2 * offset };
	Renderer::GetInstance().RenderText("SKIP", offsetRect, "Lingua.otf", color);
}

void SkipLevelButton::OnButtonUp()
{
	const auto objs = SceneManager::GetInstance().GetScene().GetGameObjectsByTag("GameManager");
	if (!objs.empty())
	{
		objs.front()->GetComponent<GameManager>().lock()->OnNotifyAll(EventType::NEXTLEVEL, std::make_shared<GameObjectArgs>(m_Owner.lock().get()));
	}
}
