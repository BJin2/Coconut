#pragma once
#include <vector>
#include <string>

class ScriptComponent;
class ActorComponent;
using namespace std;

class Actor
{
private:
	vector<ScriptComponent*> actorComponent;

public:
	//template<typename T, typename... Args> void AddComponent(Args ... args);
	void AddComponent(string fileName);
	virtual void VUpdate(float dt);
	virtual void VStart();
};