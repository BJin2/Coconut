#include "../Engines/Game.h"
#include "Actor.h"
#include "Components/ActorComponent.h"
#include "Components/ScriptComponent.h"

void Actor::VStart()
{
	for (auto comp : actorComponent)
	{
		comp->VStart();
	}
}

void Actor::VUpdate(float dt)
{
	for (auto comp : actorComponent)
	{
		comp->VUpdate(dt);
	}
}

//template<typename T, typename... Args>
//void Actor::AddComponent(Args ... args)
//{
//	T* component = new T(std::forward<Args>(args) ...);
//	actorComponent.push_back(component);
//}


void Actor::AddComponent(string fileName)
{
	ScriptComponent* component = new ScriptComponent(fileName);
	actorComponent.push_back(component);
}
