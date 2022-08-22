#include "MiniginPCH.h"
/*
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"xinput.lib")

// including Xinput.h before Windows.h gaveme the Error "# Error : "No Target Architecture" "

*/
#include "Controller.h"

class Controller::ControllerImpl
{
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	int m_ControllerIdx{};
	WORD m_ButtonsPressedCurrentFrame{};
	WORD m_ButtonsReleasedCurrentFrame{};

public:
	ControllerImpl(int controllerIdx) :
		m_ControllerIdx(controllerIdx)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		m_PreviousState = m_CurrentState;
		//CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedCurrentFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedCurrentFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
	bool IsPressed(Controller::ControllerButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned>(button);
	}

	bool IsDown(Controller::ControllerButton button) const
	{
		return m_ButtonsPressedCurrentFrame & static_cast<unsigned>(button);
	}

	bool IsUp(Controller::ControllerButton button) const
	{
		return m_ButtonsReleasedCurrentFrame & static_cast<unsigned>(button);
	}
};

Controller::Controller(int controllerIdx):
	m_pImpl( new ControllerImpl(controllerIdx))
{
}

Controller::~Controller()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void Controller::Update() const
{
	m_pImpl->Update();
}

bool Controller::IsDown(ControllerButton button) const
{
    return m_pImpl->IsDown(button);
}

bool Controller::IsUp(ControllerButton button) const
{
    return m_pImpl->IsUp(button);
}

bool Controller::IsPressed(ControllerButton button) const
{
    return m_pImpl->IsPressed(button);
}
