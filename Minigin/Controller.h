#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"xinput.lib")
#include <Xinput.h>

class Controller final
{
	class ControllerImpl; // pimpl
	ControllerImpl* m_pImpl = nullptr;
public:
	Controller(int controllerIdx);
	~Controller();
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		DPADUp = XINPUT_GAMEPAD_DPAD_UP,
		DPADDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPADLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPADRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	};

	void Update() const;
	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;

};