#pragma once
#include "Event.h"
#include "../InputCommand.hpp"
typedef InputCommand::Key KeyCode;

struct KeyEventData : IEventData
{
	bool down;
	bool up;
	bool hold;
	char placeholder;

	static const EventType type;
	KeyCode key;
};

class KeyEvent : public IEvent
{
private:
	KeyEventData* m_keyEventData;
public:
	KeyEvent() { m_keyEventData = static_cast<KeyEventData*>(m_eventData); }
	virtual EventType GetEventType()const override { return  KeyEventData::type; }
	inline bool GetKeyDown(KeyCode key) { return (m_keyEventData->key == key) && m_keyEventData->down; }
	inline bool GetKeyUp(KeyCode key) { return (m_keyEventData->key == key) && m_keyEventData->up; }
	inline bool GetKey(KeyCode key) { return (m_keyEventData->key == key) && m_keyEventData->hold; }
	inline KeyCode GetKeyCode() const { return m_keyEventData->key; }
};