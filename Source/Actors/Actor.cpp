#include "../Engines/Game.h"
#include "Actor.h"
#include "Components/ActorComponent.h"
#include "Components/Transform.h"
#include "Components/ScriptComponent.h"

Actor::Actor(std::string _name) : name(_name)
{
	transform = new Transform();
	transform->SetOwner(this);
	actorComponent.push_back(transform);
}

Actor::Actor()
{
	name = "Actor";
	transform = new Transform();
	transform->SetOwner(this);
	actorComponent.push_back(transform);
}

Actor::~Actor()
{
	for (auto comp : actorComponent)
	{
		delete comp;
	}
}

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


void Actor::AddComponent(std::string fileName)
{
	ScriptComponent* component = new ScriptComponent(fileName);
	component->SetOwner(this);
	actorComponent.push_back(component);
}
