#include "HealthComponent.h"
#include "Events.h"

void HealthComponent::OnNotifyAll(EventType event, std::shared_ptr<EventArgs> args)
{
	if (event == EventType::LOSTHEALTH)
	{
		m_Health--;

		if (m_Health <= 0)
		{
			NotifyAll(EventType::DIED, std::make_shared<GameObjectArgs>(m_Owner.lock().get()));
			return;
		}
	}
}
