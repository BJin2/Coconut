#pragma once
#include <vector>
#include "EventType.h"

namespace sf
{
	class RenderWindow;
}
class EventMapper;
class IEvent;
class IEventData;

class EventManager
{
private:
	std::vector<EventMapper*> m_registeredEventMapper;
	static EventManager* instance;
	IEvent* mainEvent;

public:
	~EventManager();
	static EventManager* Instance();
	void RegisterMapper(sf::RenderWindow* target, EventMapper* em);
	void RegisterEvent(EventType t, IEventData* data);
	void CleanMapper();
};