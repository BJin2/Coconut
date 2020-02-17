#pragma once
#include <unordered_map>
#include "EventType.h"

namespace sf
{
	class RenderWindow;
}
//Event data interface :
//Holding neccessary data for event handle
struct IEventData abstract
{
	//window that fired event
	sf::RenderWindow* target;
};

//Event interface:
//
class IEvent
{
protected:
	IEventData* m_eventData;

public:
	virtual EventType GetEventType() const { return EventType::NO_TYPE; }
	inline sf::RenderWindow* GetSource() const { return m_eventData->target; }
	inline void SetData(IEventData* ie) { m_eventData = ie; }
	inline IEventData* GetData() const { return m_eventData; }
};