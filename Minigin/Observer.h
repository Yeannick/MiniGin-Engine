#pragma once
#include "DataTypes.h"
#include <memory>
enum class EventType;
struct EventArgs
{
	virtual ~EventArgs() = default;
};
class Observer // Observer is meant to be derived from 
{
public:
	Observer() = default;
	virtual ~Observer() {};

	Observer(const Observer& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void OnNotifyAll(EventType eventType, std::shared_ptr<EventArgs> args) = 0; // need to override this to make derived class an observer

};

