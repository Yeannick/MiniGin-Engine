#pragma once
#include "UIButton.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Font.h"
class GameModeButton : public UIButton
{
public:
	GameModeButton(const std::weak_ptr<GameObject> owner,const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, const std::string& levelName) : UIButton(owner, srcRect, dstRect, path) , m_LevelName(levelName)
	{
		
		 color = SDL_Color{ 0,255,0,255 };
		
	}

	GameModeButton(const GameModeButton& other) = delete;
	GameModeButton(GameModeButton&& other) noexcept = delete;
	GameModeButton& operator=(const GameModeButton& other) = delete;
	GameModeButton& operator=(GameModeButton&& other) noexcept = delete;

	void Update()override {};
	void Render()override;
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void OnButtonDown() override {}
	void OnButtonUp() override;

private:
	const std::string m_LevelName;
	
	Font* font =nullptr;
	SDL_Color color = SDL_Color{ 255,255,255,255 };
};

