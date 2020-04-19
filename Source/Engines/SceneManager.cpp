#include "SceneManager.h"
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
	XMLDocument* doc = new XMLDocument();
	XMLError eResult = doc->LoadFile(path);

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		printf("Can not read file: %s\n", path);
	}

	scenes.push_back(doc);
}

void Scenemanger::SetActive(int index)
{
	DeleteScene();

	if (index < scenes.size())
		xmlCompiler->XMLLoad(scenes[index], scene);
	else
	{
		printf("Can not read file index: %s\n", index);
	}
}

void Scenemanger::DeleteScene()
{
	scene->DeleteAllActors();
}
