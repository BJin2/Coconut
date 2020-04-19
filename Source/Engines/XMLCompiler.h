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
	XMLError XMLLoad(XMLDocument* doc, Scene* scene);
private:
	void SaveTrnaformProperties(Actor* a, XMLDocument* doc, XMLElement* e);
	void SaveRenderProterties(Actor* a, XMLDocument* doc, XMLElement* e);
	void SaveRidgidbodyProperties(Actor* a, XMLDocument* doc, XMLElement* e);

	void LoadComponentFromXML(Actor* a, tinyxml2::XMLElement* c);
	void LoadTransformProperties(Actor* a, tinyxml2::XMLElement* e);
	void LoadRenderProperties(Actor* a, tinyxml2::XMLElement* e);
	void LoadRigidbodyProperties(Actor* a, tinyxml2::XMLElement* e);

};