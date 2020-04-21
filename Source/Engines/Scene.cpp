#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"

#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"
#include "GraphicEngine.hpp"

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

	Actor* background = AddActor("background");
	background->AddComponent<RendererComponent>();
	RendererComponent* cachedRenderer = background->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(640, 480));
	cachedRenderer->SetColor(100, 100, 100);
	background->transform->SetPosition(320, 240);

	Actor* spawner_north = AddActor("north");
	spawner_north->AddComponent<RendererComponent>();
	cachedRenderer = spawner_north->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(273, 141));
	cachedRenderer->SetTexture("../../../Assets/Textures/Spawner/Spawner_North.png");
	spawner_north->transform->SetPosition(320, 70);

	Actor* spawner_south = AddActor("south");
	spawner_south->AddComponent<RendererComponent>();
	cachedRenderer = spawner_south->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(273, 141));
	cachedRenderer->SetTexture("../../../Assets/Textures/Spawner/Spawner_South.png");
	spawner_south->transform->SetPosition(320, 480-70);

	Actor* spawner_west = AddActor("west");
	spawner_west->AddComponent<RendererComponent>();
	cachedRenderer = spawner_west->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(141, 273));
	cachedRenderer->SetTexture("../../../Assets/Textures/Spawner/Spawner_West.png");
	spawner_west->transform->SetPosition(70, 240);

	Actor* spawner_east = AddActor("east");
	spawner_east->AddComponent<RendererComponent>();
	cachedRenderer = spawner_east->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(141, 273));
	cachedRenderer->SetTexture("../../../Assets/Textures/Spawner/Spawner_East.png");
	spawner_east->transform->SetPosition(640-70, 240);

	Actor* player = AddActor("player");
	player->transform->SetPosition(320, 240);
	player->AddComponent<RendererComponent>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<AudioComponent>();

	AudioComponent* cachedAudio = player->GetComponent<AudioComponent>();
	cachedAudio->SetSound("../../../Assets/Sounds/Hit.wav");

	cachedRenderer = player->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(50, 50));
	cachedRenderer->SetTexture("../../../Assets/Textures/Player/Player_Down.png");

	Rigidbody* cachedPlayerRigidBody = player->GetComponent<Rigidbody>();
	cachedPlayerRigidBody->SetRigidbodySettings(10000.0f, 0.0f, false);//static
	cachedPlayerRigidBody->SetCurrentVelocity(Vector2(0, 0));

	Actor* bgm = AddActor("bgm");
	bgm->AddComponent<AudioComponent>();
	AudioComponent* aud = bgm->GetComponent<AudioComponent>();
	aud->Loop(true);
	aud->SetVolume(20.0f);
	aud->SetSound("../../../Assets/Sounds/file_example_WAV_1MG.wav");

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
}

void Scene::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
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

Actor* Scene::AddActor(std::string name)
{
	Actor* actor = new Actor(name);
	actors.push_back(actor);
	return actor;
}

Actor* Scene::Find(std::string name)
{
	for (auto actor : actors)
	{
		if (actor->name == name)
			return actor;
	}
	return nullptr;
}

std::vector<Actor*> Scene::FindAll(std::string name)
{
	std::vector<Actor*> result;
	for (auto actor : actors)
	{
		if (actor->name == name)
			result.push_back(actor);
	}
	return result;
}

void Scene::Destroy()
{
	for (auto actor = actors.begin(); actor != actors.end();)
	{
		if ((*actor)->destroyFlag)
		{
			delete (*actor);
			actor = actors.erase(actor);
		}
		else
		{
			actor++;
		}
	}
}

bool Scene::Destroy(std::string name)
{
	return Destroy(Find(name));
}

bool Scene::Destroy(Actor* _actor)
{
	for (auto actor : actors)
	{
		if (actor == _actor)
		{
			actor->destroyFlag = true;
			return true;
		}
	}

	return false;
}
