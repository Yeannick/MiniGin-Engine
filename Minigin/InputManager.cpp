#include "MiniginPCH.h"
#include "InputManager.h"

bool InputManager::ProcessInput()
{
	while (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == SDL_QUIT)
		{
			return false;
		}
		for (auto& keyCommand : m_KeyboardCommands)
		{
			switch (keyCommand.state)
			{
			case InputState::Down:
				if (m_Event.type == SDL_KEYDOWN && !keyCommand.WasDown && m_Event.key.keysym.scancode == keyCommand.Key)
				{
					keyCommand.WasDown = true;
					keyCommand.command->Execute();
				}
				else if (m_Event.type == SDL_KEYUP && keyCommand.WasDown && m_Event.key.keysym.scancode == keyCommand.Key)keyCommand.WasDown = false;
				break;
			case InputState::Up:
				if (m_Event.type == SDL_KEYUP && m_Event.key.keysym.scancode == keyCommand.Key)
				{
					keyCommand.command->Execute();
				}
				break;
			case InputState::Pressed:
				if (m_Event.key.keysym.scancode == keyCommand.Key)
				{
					keyCommand.command->Execute();
				}
				break;
			default:
				break;
			}
		}
	}
	Update();
	return true;
}


void InputManager::Update() const
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
	}
}

PlayerIdx InputManager::AddPlayer()
{
	PlayerIdx idx = static_cast<int>(m_pControllers.size());
	m_pControllers.push_back(std::make_unique<Controller>(idx));
	return idx;
}
void InputManager::RemovePlayer(PlayerIdx idx)
{
	if (idx > m_pControllers.size())
	{
		std::cout << " Can't remove player with Idx " << idx << " , index to high\n";
		return;
	}
	else
	{
		for (size_t i = 0; i < m_ControllerCommands.size(); i++)
		{
			if (m_ControllerCommands[i].controllerIdx == idx)
			{
				m_ControllerCommands.erase(m_ControllerCommands.begin() + i);
			}
		}
		m_pControllers.erase(m_pControllers.begin() + idx);
	}

	
}
bool InputManager::IsPressed(Controller::ControllerButton button, PlayerIdx idx)const
{
	return m_pControllers[idx]->IsPressed(button);
}
bool InputManager::IsPressed(SDL_Scancode code)const
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	return state[code];
}

bool InputManager::IsDown(Controller::ControllerButton button, PlayerIdx idx)
{
	return m_pControllers[idx]->IsDown(button);
}

bool InputManager::IsUp(Controller::ControllerButton button, PlayerIdx idx)
{
	return m_pControllers[idx]->IsUp(button);

}