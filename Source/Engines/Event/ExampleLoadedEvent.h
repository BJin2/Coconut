#pragma once
#include "Event.h"

struct ExampleLoadedEventData : IEventData
{
	std::string example;

	static const EventType type;
};

class ExampleLoadedEvent : public IEvent
{
private:
	ExampleLoadedEventData* m_exampleLoadedEventData;
public:
	ExampleLoadedEvent() { m_exampleLoadedEventData = static_cast<ExampleLoadedEventData*>(m_eventData); }
	virtual EventType GetEventType()const override { return  ExampleLoadedEventData::type; }
	inline std::string GetExampleMessage() const { return m_exampleLoadedEventData->example; }
};