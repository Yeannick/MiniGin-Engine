#include "MiniginPCH.h"
#include "InputManager.h"
#include "UiManager.h"

bool InputManager::ProcessInput()
{
	if (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == SDL_QUIT)
		{
			return false;
		}
		if (m_Event.button.button == SDL_BUTTON_LEFT)
		{
			const auto mousePos = glm::vec2{ m_Event.button.x,m_Event.button.y };
			if (m_Event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				UIManager::GetInstance().HandleButtons(InputState::Down, mousePos);
			}
			else if (m_Event.button.type == SDL_MOUSEBUTTONUP)
			{
				UIManager::GetInstance().HandleButtons(InputState::Up, mousePos);
			}
		}
	}
		Update();
		for (const auto& val : m_ControllerCommands)
		{
			switch (val.state)
			{
			case InputState::Down:
				if (IsDown(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
			case InputState::Pressed:
				if (IsPressed(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
			case InputState::Up:
				if (IsUp(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
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
	return true;
}


void InputManager::Update() const
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
	}
}

PlayerIdx InputManager::AddPlayer(bool )
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

void InputManager::AddCommand(Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIdx idx, InputState state)
{
	if (idx > m_pControllers.size())
	{
		std::cout << "Can't add command to non existing Player \n";
		return;
	}
	ControllerCommand contCom;
	contCom.command = command;
	contCom.controllerButton = button;
	contCom.controllerIdx = idx;
	contCom.state = state;

	m_ControllerCommands.push_back(contCom);
}

void InputManager::AddCommand(SDL_Scancode key, std::shared_ptr<Command> command, InputState state)
{
	KeyBoardCommand keyCommand;
	keyCommand.Key = key;
	keyCommand.command = command;
	keyCommand.state = state;

	m_KeyboardCommands.push_back(keyCommand);
}

void InputManager::RemoveCommand(Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIdx idx, InputState state)
{
	for (size_t i = 0; i < m_ControllerCommands.size(); i++)
	{
		const ControllerCommand temp = m_ControllerCommands[i];
		if (temp.controllerButton == button)
		{
			if (typeid(*temp.command) == typeid(*command))
			{
				if (temp.state == state)
				{
					if (temp.controllerIdx == idx)
					{
						m_ControllerCommands.erase(m_ControllerCommands.begin() + i);
						return;
					}
				}
			}
		}
	}
}

void InputManager::RemoveCommand(SDL_Scancode key, std::shared_ptr<Command> command, InputState state)
{
	for (size_t i = 0; i < m_KeyboardCommands.size(); ++i)
	{
		const KeyBoardCommand temp = m_KeyboardCommands.at(i);
		if (temp.Key == key)
		{
			if (typeid(*temp.command) == typeid(*command))
			{
				if (temp.state == state)
				{
					m_KeyboardCommands.erase(m_KeyboardCommands.begin() + i);
					return;
				}
			}
		}
	}
}
