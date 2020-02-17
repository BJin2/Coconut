#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ExampleLoadedEvent.h"

const EventType KeyEventData::type = EventType::KeyEvent;
const EventType MouseEventData::type = EventType::MouseEvent;
const EventType ExampleLoadedEventData::type = EventType::ExampleLoadedEvent;