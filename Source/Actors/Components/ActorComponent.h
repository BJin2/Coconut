#pragma once
#include <memory>
#include <functional>
#include <string>
#include "..\..\..\Libs\tinyxml\tinyxml.h"
#include "..\Actor.h"

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef int ComponentId;//TODO ask Galal about specific type
typedef std::hash<std::string> HashedString;

class ActorComponent
{
protected:
	//StrongActorPtr m_pOwner;
	Actor* m_pOwner;
public:
	virtual ~ActorComponent(void) { /*m_pOwner.reset();*/ }
	// These functions are meant to be overridden by the implBementation classes of the components.
	virtual void VStart() = 0;
	virtual void VUpdate(float dt) = 0;
	// This function should be overridden by the interface class.
	//virtual ComponentId VGetId(void) const { return GetIdFromName(VGetName()); }
	//virtual const char* VGetName() const = 0;
	static ComponentId GetIdFromName(const char* componentStr)
	{
		return HashedString{}(componentStr);
		//return reinterpret_cast<ComponentId>(rawId);
	}
//private:
	void SetOwner(Actor* pOwner) { m_pOwner = pOwner; }
	Actor* GetOwner() { return m_pOwner; }
};