#pragma once
#include "..\Actors\Components\ActorComponent.h"
#include <vector>

using namespace std;
class Actor
{
private:
	vector<ActorComponent> actorComp;

public:
	template<class T>
	void AddComponent();
};