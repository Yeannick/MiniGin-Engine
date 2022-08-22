#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameTime.h"


FPSComponent::FPSComponent(const std::weak_ptr<GameObject>& owner, const std::shared_ptr<Font>& font, const SDL_Color& color):
	BaseComponent(owner)
{
	if (!owner.lock()->AddComponent<TextComponent>(std::make_shared<TextComponent>(owner,"",font,color)))
	{
		std::cout << "FPSComponent: A TextComponent was already present, so no new one was added\n";
	}
	m_TextComponent = owner.lock()->GetComponent<TextComponent>();

}

void FPSComponent::FixedUpdate()
{
}

void FPSComponent::Update()
{
	++m_AccumulatedFrames;
	m_TimePassed += GameTime::GetInstance().GetDeltaTime();
	if (m_TimePassed >= 1.0) {

		//Show FPS on screen
		m_TextComponent.lock()->SetText(std::to_string(m_AccumulatedFrames) + " FPS");

		//Reset vars for next calculation
		m_TimePassed -= 1.0;
		m_AccumulatedFrames = 0;
	}
}

void FPSComponent::LateUpdate()
{
}

void FPSComponent::Render()
{
}
