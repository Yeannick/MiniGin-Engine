#pragma once

#include "Observer.h"
#include "DataTypes.h"
#include "GameObject.h"

enum class EventType
{
	SCOREGAINED,
	LOSTHEALTH,
	TELEPORTED,
	OVERLAPPLAYER,
	GAMEOVER,
	LEVELCOMPLETE,
	GAMEWON,
	DIED,
	KILL,
	NEXTLEVEL

};

struct GameObjectArgs final : public EventArgs
{
	GameObjectArgs(GameObject* Go)
		: gameobject(Go)
	{}
	virtual ~GameObjectArgs() = default;

	GameObject* gameobject = nullptr ;
};