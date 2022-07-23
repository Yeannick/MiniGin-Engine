#pragma once
#include "GameObject.h"

class Command
{
public: 
	Command(GameObject* Go);
	virtual ~Command() = default;
	virtual void Execute() = 0;

	Command(const Command & other) = delete;
	Command(Command && other) noexcept = delete;
	Command& operator=(const Command & other) = delete;
	Command& operator=(Command && other) noexcept = delete;

protected:
	GameObject* GetOwningGameObject() const;
private:
	GameObject* m_pOwningGo = nullptr;
};