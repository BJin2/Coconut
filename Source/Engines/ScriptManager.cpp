#include "ScriptManager.hpp"

ScriptManager* ScriptManager::instance;

ScriptManager::ScriptManager()
{
	pScene = nullptr;
}

ScriptManager::~ScriptManager()
{
	pScene = nullptr;
}

ScriptManager* ScriptManager::Instance()
{
	if (instance)
		return instance;
	return instance = new ScriptManager();
}


void ScriptManager::Initialize()
{

}

void ScriptManager::Start()
{

}

void ScriptManager::Update(float delta)
{

}

Actor* ScriptManager::AddActor()
{
	return nullptr;
}

void ScriptManager::SetScene(Scene* s)
{
	pScene = s;
}