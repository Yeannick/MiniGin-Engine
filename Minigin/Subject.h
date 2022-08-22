#pragma once
#include "DataTypes.h"
#include <memory>
#include <vector>
struct EventArgs;
enum class EventType;
class Observer;

class Subject
{
public:
	Subject() {};
	
	void AddObserver(Observer* pObserver);
	void AddObservers(std::vector<Observer*> pObservers);
	 void NotifyAll(EventType eventType, std::shared_ptr<EventArgs> args);

protected:
	std::vector<Observer*> m_pObservers;
private:

};


