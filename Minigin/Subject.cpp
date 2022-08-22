#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::AddObservers(std::vector<Observer*> pObservers)
{
	if (m_pObservers.empty())
	{
		m_pObservers = pObservers;
	}
	else
	{
		for (size_t i = 0; i < pObservers.size(); i++)
		{
			m_pObservers.push_back(pObservers[i]);
		}
	}
}

void Subject::NotifyAll(EventType eventType, std::shared_ptr<EventArgs> args)
{
	for (size_t i = 0; i < m_pObservers.size(); i++)
	{
		m_pObservers[i]->OnNotifyAll(eventType, args);
	}
}
