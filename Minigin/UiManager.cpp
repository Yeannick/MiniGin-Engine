#include "MiniginPCH.h"
#include "UiManager.h"

void UIManager::HandleButtons(InputState inputState, const glm::vec2& mousePos)
{
	for (size_t i = 0; i < m_Buttons.size(); ++i)
	{
		switch (inputState)
		{
		case InputState::Down:
			m_Buttons[i]->ButtonDown(mousePos);
			break;
		case InputState::Up:
			m_Buttons[i]->ButtonUp(mousePos);
			break;
		}
	}
}
