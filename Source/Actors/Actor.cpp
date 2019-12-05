#include "Actor.h"

void Actor::Start()
{
	for (auto comp : actorComponent)
	{
		comp.VInit();
	}
}

void Actor::Update(float dt)
{
	for (auto comp : actorComponent)
	{
		comp.VUpdate(dt);
	}
}

template<typename T, typename... Args>
void Actor::AddComponent(Args ... args)
{
	T component(std::forward<Args>(args) ...);
	actorComponent.push_back(component);
}