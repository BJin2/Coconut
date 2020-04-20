#include "XMLCompiler.h"
#include <iostream>
#include "../Actors/Components/Transform.h"
#include "..\Actors\Components\RendererComponent.h"
#include "..\Actors\Components\Rigidbody.h"
#include "..\Actors\Components\ScriptComponent.h"
#include "Utils.h"

#pragma region SAVE
XMLError XMLCompiler::XMLSave(const char* path, Scene* scene)
{
	XMLDocument xmlDoc;
	XMLNode* xml_scene = xmlDoc.NewElement("Scene");
	xmlDoc.InsertFirstChild(xml_scene);

	std::vector<Actor*> xml_actor = scene->GetActor();

	for (std::vector<Actor*>::iterator i = xml_actor.begin(); i != xml_actor.end(); ++i)
	{
		XMLElement* rootElement = xmlDoc.NewElement("Actor");
		SaveTrnaformProperties(*i, xmlDoc.ToDocument(), rootElement);
		SaveRenderProterties(*i, xmlDoc.ToDocument(), rootElement);
		SaveRidgidbodyProperties(*i, xmlDoc.ToDocument(), rootElement);

		xml_scene->InsertEndChild(rootElement);
	}
	XMLError result = xmlDoc.SaveFile(path);
	XMLCheckResult(result);
}

void XMLCompiler::SaveTrnaformProperties(Actor* a, XMLDocument* doc, XMLElement* e)
{
	auto transform = a->GetComponent<Transform>();
	XMLElement* newTransform = doc->NewElement("Transform");

	//char* n = new char[a->name.size() + 1];
	//XMLElement* name = doc->NewElement("Name");
	//name->SetText(n);
	//name->InsertEndChild(name);
	//newTransform->InsertEndChild(name);

	float px, py;
	px = transform->GetPosition().x;
	py = transform->GetPosition().y;

	float sx, sy;
	sx = transform->GetScale().x;
	sy = transform->GetScale().y;

	float r;
	r = transform->GetRotation();

	XMLElement* position = doc->NewElement("Position");
	// x position
	XMLElement* posElement = doc->NewElement("x");
	posElement->SetText(px);
	position->InsertEndChild(posElement);
	// y position
	posElement = doc->NewElement("y");
	posElement->SetText(py);
	position->InsertEndChild(posElement);
	// End Child position
	newTransform->InsertEndChild(position);

	XMLElement* scale = doc->NewElement("Scale");
	// x scale
	XMLElement* scaleElement = doc->NewElement("x");
	scaleElement->SetText(sx);
	scale->InsertEndChild(scaleElement);
	// y scale
	scaleElement = doc->NewElement("y");
	scaleElement->SetText(sy);
	scale->InsertEndChild(scaleElement);
	// End Child scale
	newTransform->InsertEndChild(scale);

	XMLElement* rotation = doc->NewElement("Rotation");
	rotation->SetText(r);
	newTransform->InsertEndChild(rotation);

	e->InsertEndChild(newTransform);
}

void XMLCompiler::SaveRenderProterties(Actor* a, XMLDocument* doc, XMLElement* e)
{
	auto render = a->GetComponent<RendererComponent>();

	if (render != nullptr)
	{
		XMLElement* newRender = doc->NewElement("RenderComponent");

		//Size
		float sx, sy;
		sx = render->GetSize().x;
		sy = render->GetSize().y;

		XMLElement* size = doc->NewElement("Size");
		XMLElement* sizeElement = doc->NewElement("x");
		sizeElement->SetText(sx);
		size->InsertEndChild(sizeElement);

		sizeElement = doc->NewElement("y");
		sizeElement->SetText(sy);
		size->InsertEndChild(sizeElement);
		newRender->InsertEndChild(size);

		//Color
		float r = render->GetColor().r;
		float g = render->GetColor().g;
		float b = render->GetColor().b;
		float a = render->GetColor().a;

		XMLElement* color = doc->NewElement("Color");

		XMLElement* colorElement = doc->NewElement("r");
		colorElement->SetText(r);
		color->InsertEndChild(colorElement);

		colorElement = doc->NewElement("g");
		colorElement->SetText(g);
		color->InsertEndChild(colorElement);

		colorElement = doc->NewElement("b");
		colorElement->SetText(b);
		color->InsertEndChild(colorElement);

		colorElement = doc->NewElement("a");
		colorElement->SetText(a);
		color->InsertEndChild(colorElement);

		newRender->InsertEndChild(color);

		e->InsertEndChild(newRender);
	}
}

void XMLCompiler::SaveRidgidbodyProperties(Actor* a, XMLDocument* doc, XMLElement* e)
{
	auto rb = a->GetComponent<Rigidbody>();
	if (rb != nullptr)
	{
		XMLElement* newRb = doc->NewElement("RigidbodyComponent");

		//Mass
		float m;
		m = rb->GetMass();

		XMLElement* mass = doc->NewElement("Mass");
		mass->SetText(mass);
		newRb->InsertEndChild(mass);

		//Current Velocity
		float vx, vy;
		vx = rb->GetCurrentVelocity().x;
		vy = rb->GetCurrentVelocity().y;

		XMLElement* velocity = doc->NewElement("Velocity");
		XMLElement* velocityElement = doc->NewElement("x");
		velocityElement->SetText(vx);
		velocity->InsertEndChild(velocityElement);

		velocityElement = doc->NewElement("y");
		velocityElement->SetText(vy);
		velocity->InsertEndChild(velocityElement);
		newRb->InsertEndChild(velocity);

		//Bounciness
		float b;
		b = rb->GetBounciness();
		XMLElement* bounce = doc->NewElement("Bounciness");
		bounce->SetText(b);
		newRb->InsertEndChild(bounce);

		e->InsertEndChild(newRb);
	}
}
#pragma endregion
#pragma region LOAD
XMLError XMLCompiler::XMLLoad(XMLDocument* doc, Scene* scene)
{
	XMLNode* xml_scene = doc->FirstChildElement("Scene");
	if (xml_scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* element = xml_scene->FirstChildElement("Actor");
	if (element == nullptr) {
		std::cout << "Element null" << std::endl;
		return XML_ERROR_PARSING_ELEMENT;
	}

	while (element != nullptr)
	{
		Actor* actor = scene->AddActor();
		XMLElement* component = element->FirstChildElement();

		while (component != nullptr)
		{
			LoadComponentFromXML(actor, component);
			component = component->NextSiblingElement();
		}

		element = element->NextSiblingElement("GameObject");
	}
}

void XMLCompiler::LoadComponentFromXML(Actor* a, tinyxml2::XMLElement* e)
{
	std::string name = e->Name();
	if (name == "Transform") LoadTransformProperties(a, e);
	else if (name == "RenderComponent") LoadRenderProperties(a, e);
	else if (name == "RigidbodyComponent") LoadRigidbodyProperties(a, e);
	//else if (name == "ScriptComponent") a->AddComponent<ScriptComponent>();
}

void XMLCompiler::LoadTransformProperties(Actor* a, tinyxml2::XMLElement* e)
{
	XMLElement* property = e->FirstChildElement();

	while (property != nullptr)
	{
		const char* n = new char[50];
		switch (*property->Name())
		{
		case * "Name":
			property->QueryStringAttribute("Name", &n);
			a->name = n;
			break;

		case * "Position":
			float px, py;
			property->FirstChildElement("x")->QueryFloatText(&px);
			property->FirstChildElement("y")->QueryFloatText(&py);
			a->transform->SetPosition(Vector2(px, py));
			break;

		case * "Scale":
			float sx, sy;
			property->FirstChildElement("x")->QueryFloatText(&sx);
			property->FirstChildElement("y")->QueryFloatText(&sy);
			a->transform->SetScale(Vector2(sx, sy));
			break;

		case * "Rotation":
			float angle;
			property->QueryFloatText(&angle);
			a->transform->SetRotation(angle);
			break;

		default:
			break;
		}
		property = property->NextSiblingElement();
	}
}

void XMLCompiler::LoadRenderProperties(Actor* a, tinyxml2::XMLElement* e)
{
	a->AddComponent<RendererComponent>();
	RendererComponent* render = a->GetComponent<RendererComponent>();

	XMLElement* property = e->FirstChildElement();

	while (property != nullptr)
	{
		switch (*property->Name())
		{
		case * "Size":
			float px, py;
			property->FirstChildElement("x")->QueryFloatText(&px);
			property->FirstChildElement("y")->QueryFloatText(&py);
			render->SetSize(sf::Vector2f(px, py));
			break;

		case * "Color":
			float r, g, b, a;
			property->FirstChildElement("r")->QueryFloatText(&r);
			property->FirstChildElement("g")->QueryFloatText(&g);
			property->FirstChildElement("b")->QueryFloatText(&b);
			property->FirstChildElement("a")->QueryFloatText(&a);
			render->SetColor(sf::Color(r, g, b, a));
			break;

		default:
			break;
		}
		property = property->NextSiblingElement();
	}
}

void XMLCompiler::LoadRigidbodyProperties(Actor* a, tinyxml2::XMLElement* e)
{
	a->AddComponent<Rigidbody>();
	Rigidbody* rb = a->GetComponent<Rigidbody>();

	XMLElement* property = e->FirstChildElement();

	while (property != nullptr)
	{
		switch (*property->Name())
		{
		case * "Velocity":
			float vx, vy;
			property->FirstChildElement("x")->QueryFloatText(&vx);
			property->FirstChildElement("y")->QueryFloatText(&vy);
			rb->SetCurrentVelocity(Vector2(vx, vy));
			break;

		case * "Mass":
			float m;
			property->QueryFloatText(&m);
			rb->SetMass(m);
			break;

		case * "Bounciness":
			float b;
			property->QueryFloatText(&b);
			rb->SetBounciness(b);
			break;

		default:
			break;
		}
		property = property->NextSiblingElement();
	}
}
#pragma endregion