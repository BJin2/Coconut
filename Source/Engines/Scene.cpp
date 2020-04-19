#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"
#include "../../Engines/InputCommand.hpp"

#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"
#include "GraphicEngine.hpp"

class RenderComponent;

Scene::~Scene()
{
	for (auto actor : actors)
	{
		delete actor;
	}
}

void Scene::Initialize()
{
	std::string name = "../../Lua/test.lua";

	//*/
	Actor* first = new Actor();
	first->AddComponent(name);
	first->AddComponent<AudioComponent>();

	first->AddComponent<RendererComponent>();
	first->AddComponent<Rigidbody>();
	Rigidbody* firstRigidbody = first->GetComponent<Rigidbody>();
	firstRigidbody->SetRigidbodySettings(2.0f, 0.8f, false);
	firstRigidbody->SetCurrentVelocity(Vector2(60, 0));
	first->transform->SetPosition(100, 50);

	//Actor* second = new Actor();
	//second->AddComponent(name);
	//second->AddComponent<AudioComponent>();
	//second->AddComponent<RendererComponent>();
	//second->AddComponent<Rigidbody>();
	//Rigidbody* secondRigidbody = second->GetComponent<Rigidbody>();
	//secondRigidbody->SetCurrentVelocity(Vector2(-30, 0));
	//second->transform->SetPosition(200, 50);

	Actor* third = new Actor();
	third->AddComponent<RendererComponent>();
	third->AddComponent<Rigidbody>();
	Rigidbody* thirdRigidbody = third->GetComponent<Rigidbody>();
	thirdRigidbody->SetRigidbodySettings(2.0f, 0.8f, false);
	thirdRigidbody->SetCurrentVelocity(Vector2(-10, 0));
	third->transform->SetPosition(250, 50);

	Actor* fourth = new Actor();
	fourth->AddComponent<RendererComponent>();
	fourth->AddComponent<Rigidbody>();
	Rigidbody* fourthRigidbody = fourth->GetComponent<Rigidbody>();
	fourthRigidbody->SetRigidbodySettings(2.0f, 0.8f, false);
	fourthRigidbody->SetCurrentVelocity(Vector2(-50, 0));
	fourth->transform->SetPosition(600, 50);
	
	actors.push_back(first);
	//actors.push_back(second);
	actors.push_back(third);
	actors.push_back(fourth);
	/*/
	Actor* third = new Actor();
	third->AddComponent(name);
	third->AddComponent<RendererComponent>();
	third->AddComponent<Rigidbody>();
	third->AddComponent<AudioComponent>();
	Rigidbody* thirdRigidbody = third->GetComponent<Rigidbody>();
	thirdRigidbody->SetRigidbodySettings(0.0f, 0.8f, false);
	third->transform->SetPosition(450, 100);


	Actor* fourth = new Actor();
	fourth->AddComponent<RendererComponent>();
	fourth->AddComponent<Rigidbody>();
	Rigidbody* fourthRigidbody = fourth->GetComponent<Rigidbody>();
	fourthRigidbody->SetRigidbodySettings(1.0f, 0.8f, false);
	fourthRigidbody->SetCurrentVelocity(Vector2(0, -30));
	fourth->transform->SetPosition(450, 250);

	actors.push_back(third);
	actors.push_back(fourth);
	//*/


	ExampleLoadedEventData data;
	data.example = "Scene Loaded";
	data.target = GraphicEngine::Instance()->GetGameScreen();
	EventManager::Instance()->RegisterEvent(data.type, &data);
}

void Scene::Start()
{
	for (auto actor : actors)
	{
		actor->VStart();
	}

	actors[0]->GetComponent<AudioComponent>()->Play();
	sf::Color colors[4] = { sf::Color::Red, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta};
	for (int i = 0; i < 3; i++)
	{
		actors[i]->GetComponent<RendererComponent>()->SetColor(colors[i]);
	}
}

void Scene::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
	}
	//Input and translation testing
	if (InputCommand::GetKeyDown(InputCommand::Key::D))
	{
		actors[0]->transform->Translate(Vector2(1, 0), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::A))
	{
		actors[0]->transform->Translate(Vector2(-1, 0), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::W))
	{
		actors[0]->transform->Translate(Vector2(0, 1), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::S))
	{
		actors[0]->transform->Translate(Vector2(0, -1), 3 * delta);
	}
}

void Scene::DeleteAllActors()
{
	for (auto a : actors)
	{
		delete a;
	}
	actors.clear();
}

std::vector<Actor*> Scene::GetActor()
{
	return actors;
}

Actor* Scene::AddActor()
{
	Actor* actor = new Actor();
	actors.push_back(actor);
	return actor;
}
