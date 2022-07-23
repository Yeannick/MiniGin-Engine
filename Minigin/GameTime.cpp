#include "MiniginPCH.h"
#include "GameTime.h"

void GameTime::SetDeltaTime(float dt)
{
	m_DeltaTime = dt;

}

float GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
