#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "ResourceManager.h"

TextComponent::TextComponent(const std::weak_ptr<GameObject>& owner, const std::string text, const std::shared_ptr<Font> font, const SDL_Color color):
	BaseComponent(owner),
	m_Text(text),
	m_Font(font),
	m_Color(color)
{
	if (!text.empty())
		m_NeedsUpdate = true;
}
TextComponent::TextComponent(const std::weak_ptr<GameObject>& owner):BaseComponent(owner),m_Font(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)), m_TextTexture(nullptr), m_Color({ 255,255,255 })
{
		m_Text = "0";
		m_NeedsUpdate = true;
}
void TextComponent::FixedUpdate()
{
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
	
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::LateUpdate()
{
}

void TextComponent::Render()
{
	if (m_TextTexture != nullptr)
	{

		glm::vec3 pos = m_Owner.lock()->GetTransform().GetPosition();
		Renderer::GetInstance().AddToRenderQueue(*m_TextTexture, pos.x, pos.y, 0, pos.z);
		//Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_TextTexture = texture;
}
