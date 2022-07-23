#include "MiniginPCH.h"
#include "Command.h"

Command::Command(GameObject* Go):
    m_pOwningGo(Go)
{
}

GameObject* Command::GetOwningGameObject() const
{
    return m_pOwningGo;
}
