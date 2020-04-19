#include "XMLCompiler.h"
#include <iostream>
#include "../Actors/Components/Transform.h"
#include "..\Actors\Components\RendererComponent.h"
#include "..\Actors\Components\Rigidbody.h"
#include "..\Actors\Components\ScriptComponent.h"
#include "Utils.h"

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

void XMLCompiler::SaveTrnaformProperties(Actor* a, XMLDocument* doc, XMLElement* e)
{
	auto transform = a->GetComponent<Transform>();
	if (transform != nullptr)
	{
		XMLElement* newtrasform = doc->NewElement("Transform");

		//Postion
		float px, py;
		px = transform->GetPosition().x;
		py = transform->GetPosition().y;

		XMLElement* position = doc->NewElement("Position");

		XMLElement* posElement = doc->NewElement("x");
		posElement->SetText(px);
		posElement->InsertEndChild(posElement);

		posElement = doc->NewElement("y");
		posElement->SetText(py);
		posElement->InsertEndChild(posElement);

		//Scale
		newtrasform->InsertEndChild(position);

		float sx, sy;
		sx = a->transform->GetScale().x;
		sy = a->transform->GetScale().y;

		XMLElement* scale = doc->NewElement("scale");

		XMLElement* scaleElement = doc->NewElement("x");
		scaleElement->SetText(sx);
		scale->InsertEndChild(scaleElement);

		scaleElement = doc->NewElement("y");
		scaleElement->SetText(sy);
		scale->InsertEndChild(scaleElement);

		newtrasform->InsertEndChild(scale);

		//Rotation
		float r;
		r = a->transform->GetRotation();

		XMLElement* rotation = doc->NewElement("rotation");
		rotation->SetText(r);
		newtrasform->InsertEndChild(rotation);

		e->InsertEndChild(newtrasform);
	}
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

		XMLElement* size = doc->NewElement("size");
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

		XMLElement* color = doc->NewElement("color");

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

		XMLElement* mass = doc->NewElement("mass");
		mass->SetText(mass);
		newRb->InsertEndChild(mass);

		//Current Velocity
		float vx, vy;
		vx = rb->GetCurrentVelocity().x;
		vx = rb->GetCurrentVelocity().y;

		XMLElement* velocity = doc->NewElement("velocity");
		XMLElement* velocityElement = doc->NewElement("x");
		velocityElement->SetText(vx);
		velocity->InsertEndChild(velocityElement);

		XMLElement* velocityElement = doc->NewElement("y");
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

void XMLCompiler::LoadComponentFromXML(Actor* a, tinyxml2::XMLElement* e)
{
	std::string name = e->Name();
	if (name == "Transform") LoadTransformProperties(a, e);
	else if (name == "RenderComponent") LoadRenderProperties(a, e);
	else if (name == "RigidbodyComponent") LoadRigidbodyProperties(a, e);
	else if (name == "ScriptComponent") a->AddComponent<ScriptComponent>();
}

void XMLCompiler::LoadTransformProperties(Actor* a, tinyxml2::XMLElement* e)
{
	XMLElement* property = e->FirstChildElement();

	while (property != nullptr)
	{
		switch (*property->Name())
		{
		case * "position":
			float px, py;
			property->FirstChildElement("x")->QueryFloatText(&px);
			property->FirstChildElement("y")->QueryFloatText(&py);
			a->transform->SetPosition(Vector2(px, py));
			break;

		case * "scale":
			float sx, sy;
			property->FirstChildElement("x")->QueryFloatText(&sx);
			property->FirstChildElement("y")->QueryFloatText(&sy);
			a->transform->SetScale(Vector2(sx, sy));
			break;

		case * "rotation":
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
		case * "size":
			float px, py;
			property->FirstChildElement("x")->QueryFloatText(&px);
			property->FirstChildElement("y")->QueryFloatText(&py);
			render->SetSize(sf::Vector2f(px, py));
			break;

		case * "color":
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
		case * "velocity":
			float vx, vy;
			property->FirstChildElement("x")->QueryFloatText(&vx);
			property->FirstChildElement("y")->QueryFloatText(&vy);
			rb->SetCurrentVelocity(Vector2(vx, vy));
			break;

		case * "mass":
			float m;
			property->QueryFloatText(&m);
			rb->SetMass(m);
			break;

		case * "bounciness":
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