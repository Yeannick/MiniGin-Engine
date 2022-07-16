#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "SDL.h"
#include "GameObject.h"
#include "Texture2D.h"


class TextComponent : public BaseComponent
{
public :
	TextComponent(const std::weak_ptr<GameObject>& owner, const std::string text, const std::shared_ptr<Font> font, const SDL_Color color);

	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void SetText(const std::string& text);
	virtual void SetTexture(const std::shared_ptr<Texture2D>& texture);

private: 
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	SDL_Color m_Color;
	std::shared_ptr<Texture2D> m_TextTexture;
};

