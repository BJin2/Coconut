#pragma once
#include "Scene.h"
#include "..\Actors\Actor.h"
#include "..\..\Libs\tinyxml\tinyxml.h"
#include "XMLCompiler.h"
using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class Scenemanger
{
public:
	Scenemanger(Scene* s);
	~Scenemanger();
	XMLError LoadScene(const char* path);
	void SetActive(int index);
private:
	std::vector<XMLDocument*> scenes;
	Scene* scene;
	XMLCompiler* xmlCompiler;
	void DeleteScene();
};
