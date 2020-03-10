#include <SFML/Graphics.hpp>
#include "EventMapper.h"
#include "Event.h"
#include "EventHandler.h"

EventMapper::~EventMapper()
{
	for (auto e : m_registeredHandler)
	{
		if (e.second)
			delete e.second;
	}
	m_registeredHandler.clear();
}

void EventMapper::SetOnEvent(void(*passedPointer)(const IEvent* e), EventType t)
{
	auto it = m_registeredHandler.find(t);
	if (it != m_registeredHandler.end())
	{
		it->second->SetHandle(passedPointer);
	}
	else
	{
		EventHandler* p = new EventHandler();
		p->SetHandle(passedPointer);
		m_registeredHandler.insert(std::make_pair(t, p));
	}
}

bool EventMapper::HandleEvent(EventType t, IEvent* e)
{
	auto it = m_registeredHandler.find(t);
	if (it != m_registeredHandler.end())
	{
		it->second->handle(e);
		return true;
	}
	else
	{
		std::cout << "NO HANDLER" << std::endl;
		return false;
	}
}

void EventMapper::CleanMapper()
{
	for (auto it = m_registeredHandler.begin(); it != m_registeredHandler.end(); it++)
	{
		if (it->second != nullptr)
		{
			delete it->second;
		}
	}

	m_registeredHandler.clear();
}
