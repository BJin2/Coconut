#pragma once
#include "Event.h"
#include "../InputCommand.hpp"
typedef InputCommand::Key KeyCode;

struct MouseEventData : IEventData
{
	short screenX;
	short screenY;

	short windowX;
	short windowY;

	// TODO mouse button check

	static const EventType type;
	KeyCode button;
};

class MouseEvent : public IEvent
{
private:
	MouseEventData m_mouseEventData;

public:
	MouseEvent() {m_mouseEventData = *static_cast<MouseEventData*>(m_eventData);}
	virtual EventType GetEventType()const override { return  MouseEventData::type;}
	inline unsigned short GetScreenX() const { return m_mouseEventData.screenX; }
	inline unsigned short GetScreenY() const { return m_mouseEventData.screenY; }
	inline unsigned short GetWindowX() const { return m_mouseEventData.windowX; }
	inline unsigned short GetWindowY() const { return m_mouseEventData.windowY; }

	//TODO mouse button check
	//inline bool GetMouseButtonDown(KeyCode button) { return m_mouseEventData.down[button]; }
	//inline bool GetMouseButtonUp(KeyCode button) { return m_mouseEventData.up[button]; }
	//inline bool GetMouseButton(KeyCode button) { return m_mouseEventData.hold[button]; }
};