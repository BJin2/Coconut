#pragma once
#include <vector>
#include <string>

class ActorComponent;
class Transform;

class Actor
{
private:
	std::vector<ActorComponent*> actorComponent;
	
public:
	Actor();
	Actor(std::string _name);
	~Actor();
	virtual void VUpdate(float dt);
	virtual void VStart();

	Transform* transform;
	std::string name;
	bool destroyFlag;

	//template<typename T, typename... Args> void AddComponent(Args ... args);
	void AddComponent(std::string fileName);

	template<typename T>
	void AddComponent();

	template<typename T>
	T* GetComponent();
};


//Template function definition
template<typename T>
inline void Actor::AddComponent()
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
inline T* Actor::GetComponent()
{
	for (auto comp : actorComponent)
	{
		if (typeid(*comp) == typeid(T))
		{
			return dynamic_cast<T*>(comp);
		}
	}
	return nullptr;
}
