#pragma once

class Scene;
class Actor;

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();
	static ScriptManager* Instance();

	void Initialize();
	void Start();
	void Update(float delta);

	void SetScene(Scene* s);

	Actor* AddActor();

private:
	static ScriptManager* instance;
	Scene* pScene;
};
