#pragma once
#include "UIButton.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "UiManager.h"
class SkipLevelButton :public UIButton
{
public:
	SkipLevelButton(const std::weak_ptr<GameObject> owner, const SDL_Rect& srcRect,  const SDL_Rect& dstRect,  const std::string& path, bool IsPressed = true)
		:UIButton(owner, srcRect, dstRect, path, IsPressed) 
	{
		UIManager::GetInstance().AddButton(this);
		 color = SDL_Color{ 0,255,0,255 };
		
	}

	SkipLevelButton(const SkipLevelButton& other) = delete;
	SkipLevelButton(SkipLevelButton&& other) noexcept = delete;
	SkipLevelButton& operator=(const SkipLevelButton& other) = delete;
	SkipLevelButton& operator=(SkipLevelButton&& other) noexcept = delete;

	void Update()override {};
	void Render()override;
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void OnButtonDown() override {}
	void OnButtonUp() override;
private:
	
	Font* font = nullptr;
	SDL_Color color = SDL_Color{ 255,255,255,255 };
};

