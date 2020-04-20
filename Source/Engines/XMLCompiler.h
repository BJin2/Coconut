#pragma once
#include "Scene.h"
#include "..\Actors\Actor.h"
#include "..\..\Libs\tinyxml\tinyxml.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class XMLCompiler
{
public:
	XMLError XMLSave(const char* path, Scene* scene);
	XMLError XMLLoad(const char* path, Scene* scene);
	XMLError XMLLoad(tinyxml2::XMLDocument* doc, Scene* scene);
private:
	void SaveTrnaformProperties(Actor* a, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* e);
	void SaveRenderProterties(Actor* a, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* e);
	void SaveRidgidbodyProperties(Actor* a, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* e);

	void LoadComponentFromXML(Actor* a, tinyxml2::XMLElement* c);
	void LoadTransformProperties(Actor* a, tinyxml2::XMLElement* e);
	void LoadRenderProperties(Actor* a, tinyxml2::XMLElement* e);
	void LoadRigidbodyProperties(Actor* a, tinyxml2::XMLElement* e);
	std::vector<tinyxml2::XMLDocument*> scenes;
};