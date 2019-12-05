#pragma once
#include <vector>

class ActorComponent;
using namespace std;

class Actor
{
private:
	vector<ActorComponent*> actorComponent;

public:
	template<typename T, typename... Args> void AddComponent(Args ... args);
	virtual void Update(float dt);
	virtual void Start();
};