#pragma once
#include "../Actors/Components/ScriptComponent.h"
#include "Scene.h"

class ScriptManager
{
private:
	Scene* pScene;

public:
	ScriptManager(Scene* s);
	~ScriptManager();

	void Initialize();
	void Start();
	void Update(float delta);

	Actor* AddActor();
};
