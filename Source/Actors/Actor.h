#pragma once
#include <vector>
#include <string>

class ActorComponent;

class Actor
{
private:
	std::vector<ActorComponent*> actorComponent;

public:
	//template<typename T, typename... Args> void AddComponent(Args ... args);
	void AddComponent(std::string fileName);
	template<typename T>
	void AddComponent();
	template<typename T>
	T GetComponent();
	virtual void VUpdate(float dt);
	virtual void VStart();
};
template<typename T>
void Actor::AddComponent()
{
	try
	{
		T* temp = new T();
		temp->SetOwner(this);
		actorComponent.push_back(temp);
	}
	catch (const std::exception & e)
	{
		printf("Component Error");
	}
}

template<typename T>
T Actor::GetComponent()
{
	for (auto comp : actorComponent)
	{
		if (typeid(comp) == typeid(T))
		{
			return comp;
		}
	}
	return nullptr;
}
