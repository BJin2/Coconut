#include "SceneManager.h"
#include "../Actors/Components/AudioComponent.h"
using namespace tinyxml2;

Scenemanger::Scenemanger(Scene* s)
{
	scene = s;
	xmlCompiler = new XMLCompiler();
}

Scenemanger::~Scenemanger()
{
	for (auto s : scenes)
	{
		delete s;
	}

	scenes.clear();
}

XMLError Scenemanger::LoadScene(const char* path)
{

	for (int i = 0; i < scene->GetActor().size(); i++)
	{
		if (scene->GetActor()[i]->GetComponent<AudioComponent>() != nullptr)
		{
			scene->GetActor()[i]->GetComponent<AudioComponent>()->Stop();
		}
	}
	scene->GetActor().clear();

	XMLDocument* doc = new XMLDocument();
	
	XMLError eResult = doc->LoadFile(path);

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		printf("Can not read file: %s\n", path);
	}

	scenes.push_back(doc);
	return eResult;
}

void Scenemanger::SetActive(int index)
{
	DeleteScene();

	if (index < scenes.size())
		xmlCompiler->XMLLoad(scenes[index], scene);
	else
	{
		printf("Can not find index : %s\n", index);
	}
}

void Scenemanger::DeleteScene()
{
	scene->DeleteAllActors();
}
