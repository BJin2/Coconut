#pragma once
#include <unordered_map>
#include "EventType.h"

namespace sf
{
	class RenderWindow;
}
class IEvent;
class EventHandler;

class EventMapper
{
private:
	sf::RenderWindow* targetWindow;
	std::unordered_map<EventType, EventHandler*> m_registeredHandler;

public:
	~EventMapper();
	void SetOnEvent(void(* passedPointer)(const IEvent* e), EventType t);
	bool HandleEvent(EventType t, IEvent* data);
	void CleanMapper();
	sf::RenderWindow* GetTargetWindow() { return targetWindow; }
	void SetTargetWindow(sf::RenderWindow* target) { targetWindow = target; }
};