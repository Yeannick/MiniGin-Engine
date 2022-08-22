#include "MiniginPCH.h"
#include "UIButton.h"
#include "ResourceManager.h"
#include "UiManager.h"
#include "Renderer.h"

UIButton::UIButton(const std::weak_ptr<GameObject> owner, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, bool IsPressed): BaseComponent(owner),
m_SrcRect (srcRect),
m_DstRect (dstRect),

IsPressed(IsPressed)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	UIManager::GetInstance().AddButton(this);
}

UIButton::~UIButton()
{
	UIManager::GetInstance().RemoveButton(this);
}

void UIButton::Render()
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, m_DstRect, false);
}

void UIButton::ButtonDown(const glm::vec2& mousePos)
{
	if (IsOverlapping(mousePos))
	{
		if (IsPressed)
		{
			m_SrcRect.x += m_SrcRect.w;
			m_HasChangedSrcRect = true;
		}

		OnButtonDown();
	}
}

void UIButton::ButtonUp(const glm::vec2& mousePos)
{
	if (IsPressed && m_HasChangedSrcRect)
	{
		m_SrcRect.x -= m_SrcRect.w;
		m_HasChangedSrcRect = false;
		if (IsOverlapping(mousePos))
		{
			OnButtonUp();
		}
		return;
	}

	if (!IsOverlapping(mousePos))
		return;
	if (!IsPressed)
		OnButtonUp();
}
