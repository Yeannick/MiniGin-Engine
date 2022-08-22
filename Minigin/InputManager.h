#pragma once
//#include <XInput.h>
#include "Singleton.h"
#include "Controller.h"
#include "Command.h"
#include <memory>

#define PlayerIdx unsigned int 
enum class InputState
{
	Down,
	Pressed,
	Up
};
enum class MouseButton
{
	Left,
	Middle,
	Right
};

struct ControllerCommand
{
	ControllerCommand() = default;
	Controller::ControllerButton controllerButton;
	InputState state;
	std::shared_ptr<Command>command;
	PlayerIdx controllerIdx;
};
struct KeyBoardCommand
{
	KeyBoardCommand() = default;
	SDL_Scancode Key;
	InputState state;
	std::shared_ptr<Command>command;
	bool WasDown = false;
};
class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();
	void Update() const;

	PlayerIdx AddPlayer(bool kb = false);
	void RemovePlayer(PlayerIdx idx);

	bool IsPressed(Controller::ControllerButton button,PlayerIdx idx)const; // controller
	bool IsPressed(SDL_Scancode code) const; // keyboard

	bool IsDown(Controller::ControllerButton button, PlayerIdx idx); // controller
	bool IsUp(Controller::ControllerButton button, PlayerIdx idx);

	void AddCommand(Controller::ControllerButton button, std::shared_ptr<Command>command, PlayerIdx idx, InputState state); // controller
	void AddCommand(SDL_Scancode key, std::shared_ptr<Command> command, InputState state); // keyboard

	void RemoveCommand(Controller::ControllerButton button, std::shared_ptr<Command>command,PlayerIdx idx, InputState state); // controller
	void RemoveCommand(SDL_Scancode key , std::shared_ptr<Command> command,InputState state); // keyboard


	//bool IsPressed(ControllerButton button) const;
private:
	std::vector<KeyBoardCommand>m_KeyboardCommands;
	SDL_Event m_Event;
	std::vector<ControllerCommand>m_ControllerCommands;
	std::vector<std::unique_ptr<Controller>> m_pControllers;
};


