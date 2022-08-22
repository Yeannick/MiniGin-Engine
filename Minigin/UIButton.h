#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "SDL.h"

class UIButton  : public BaseComponent
{
public:
	UIButton(const std::weak_ptr<GameObject> owner,const SDL_Rect& srcRect, const SDL_Rect& dstRect,const std::string& path, bool IsPressed = true);
	~UIButton() override;

	UIButton(const UIButton& other) = delete;
	UIButton(UIButton&& other) noexcept = delete;
	UIButton& operator=(const UIButton& other) = delete;
	UIButton& operator=(UIButton&& other) noexcept = delete;

	virtual void Update()override {};
	void Render()override;
	virtual void FixedUpdate()override {};
	virtual void LateUpdate()override {};

	void ButtonDown(const glm::vec2& mousePos);
	void ButtonUp(const glm::vec2& mousePos);

	virtual void OnButtonDown() {}
	virtual void OnButtonUp() {}

protected:
	virtual bool IsOverlapping(const glm::vec2& mousePos) const
	{
		return mousePos.x >= m_DstRect.x && mousePos.y >= m_DstRect.y && mousePos.x <= m_DstRect.x + m_DstRect.w && mousePos.y <= m_DstRect.y + m_DstRect.h; // including borders of rectangle
	}
	SDL_Rect m_SrcRect{};
	SDL_Rect m_DstRect{};

	std::shared_ptr<Texture2D> m_pTexture  ;
private:
	bool IsPressed;
	bool m_HasChangedSrcRect = false ;

};

