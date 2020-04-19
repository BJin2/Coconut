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

float fire_timer = 0;
Vector2 direction = Vector2(0, 1);

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
	player->AddComponent<RendererComponent>();
	player->AddComponent<Rigidbody>();
	Rigidbody* cachedPlayerRigidBody = player->GetComponent<Rigidbody>();
	cachedPlayerRigidBody->SetRigidbodySettings(10000.0f, 0.0f, false);//static
	cachedPlayerRigidBody->SetCurrentVelocity(Vector2(0, 0));
	cachedRenderer = player->GetComponent<RendererComponent>();
	cachedRenderer->SetSize(Vector2(50, 50));
	cachedRenderer->SetTexture("../../../Assets/Textures/Player/Player_Down.png");
	player->transform->SetPosition(320 - 25, 240 - 25);

	Actor* bgm = AddActor("bgm");
	bgm->AddComponent<AudioComponent>();

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

	Find("bgm")->GetComponent<AudioComponent>()->Play();
}

void Scene::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
	}
	fire_timer += delta;
	//printf("Timer : %f\n", delta);
	//Hardcoded game logic
	if (InputCommand::GetKeyDown(InputCommand::Key::D))
	{
		//Find("player")->transform->Translate(Vector2(1, 0), 3 * delta);
		Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Right.png");
		direction = Vector2(1, 0);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::A))
	{
		//Find("player")->transform->Translate(Vector2(-1, 0), 3 * delta);
		Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Left.png");
		direction = Vector2(-1, 0);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::W))
	{
		//Find("player")->transform->Translate(Vector2(0, 1), 3 * delta);
		Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Up.png");
		direction = Vector2(0, -1);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::S))
	{
		//Find("player")->transform->Translate(Vector2(0, -1), 3 * delta);
		Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Down.png");
		direction = Vector2(0, 1);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::Space))
	{
		if (fire_timer >= 0.2f)
		{
			Vector2 playerHalfSize = Find("player")->GetComponent<RendererComponent>()->GetSize() * 0.5f;
			Vector2 playerCenter = Find("player")->transform->GetPosition() + playerHalfSize;
			Vector2 projectileHalfSize = Vector2(7, 7);

			Actor* projectile = AddActor("projectile");
			projectile->AddComponent<RendererComponent>();
			projectile->AddComponent<Rigidbody>();
			RendererComponent* cachedRenderer = projectile->GetComponent<RendererComponent>();
			cachedRenderer->SetSize(projectileHalfSize*2.0f);
			cachedRenderer->SetTexture("../../../Assets/Textures/projectile.png");
			
			Rigidbody* cachedRigidBody = projectile->GetComponent<Rigidbody>();
			cachedRigidBody->SetRigidbodySettings(1.0f, 0.0f, false);//static
			cachedRigidBody->SetCurrentVelocity(direction * 100.0f);
			cachedRigidBody->SetAABB();
			float x = playerCenter.x + (direction.x * playerHalfSize.x) + (direction.x * projectileHalfSize.x);
			float y = playerCenter.y + (direction.y * playerHalfSize.y) + (direction.y * projectileHalfSize.y);
			printf("Projectile pos : %f\n", y);
			projectile->transform->SetPosition(x, y);
			fire_timer = 0;
		}
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
