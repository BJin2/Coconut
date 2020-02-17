#pragma once
#include <iostream>

class IEvent;

class EventHandler
{
private:
	void(*_handle)(const IEvent* e);
	static void DefaultHandle(const IEvent* e)
	{
		std::cout << "EventHandler.DefaultHandler" << std::endl;;
	}

public:
	EventHandler()
	{
		_handle = DefaultHandle;
	}
	void SetHandle(void(*passedPointer)(const IEvent*)) { _handle = passedPointer; }
	void handle(IEvent* e) { _handle(e); }
};