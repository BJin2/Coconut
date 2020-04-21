#include "Scene.h"
#include "Game.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"
#include "../../Engines/InputCommand.hpp"

#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"
#include "GraphicEngine.hpp"

#pragma region Temporary variables
//temporary variables. Will be moved to script
float fire_timer = 0;
float spawn_timer = 0;
Vector2 direction = Vector2(0, 1);
std::string spawner_direction[4] = { "east", "south", "west", "north" };
bool gameover = false;
#pragma endregion

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
	aud->Play();

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

#pragma region Hard coded game logic
	Find("player")->GetComponent<Rigidbody>()->SetOnCollide([](void* _player) {
		printf("Game Over\n");

		std::vector<Actor*> enemies = Game::GetCurrentScene()->FindAll("enemy");
		std::vector<Actor*> projectiles = Game::GetCurrentScene()->FindAll("projectile");

		for (auto enemy : enemies)
		{
			Rigidbody* er = enemy->GetComponent<Rigidbody>();
			Vector2 reverseVelocity = er->GetCurrentVelocity() * -1.0f;
			er->SetCurrentVelocity(reverseVelocity);
		}
		for (auto projectile : projectiles)
		{
			Rigidbody* pr = projectile->GetComponent<Rigidbody>();
			Vector2 reverseVelocity = pr->GetCurrentVelocity() * -1.0f;
			pr->SetCurrentVelocity(reverseVelocity);
		}

		Actor* game_over = Game::GetCurrentScene()->AddActor("gameover");
		game_over->AddComponent<RendererComponent>();
		game_over->transform->SetPosition(320, 240);
		RendererComponent* cachedRenderer = game_over->GetComponent<RendererComponent>();
		cachedRenderer->SetSize(Vector2(640, 480));
		cachedRenderer->SetTexture("../../../Assets/Textures/gameover.png");

		gameover = true;
		}, Find("player"));
#pragma endregion
}

void Scene::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
	}
	
#pragma region Hard coded game logic
	if (gameover)
		return;

	fire_timer += delta;
	spawn_timer += delta;
	if (spawn_timer >= 3.0f)
	{
		Vector2 dir = Vector2(0, 0);
		for (int i = 0; i < 4; i++)
		{
			Vector2 spawnPos = Find(spawner_direction[i])->transform->GetPosition();
			dir = Find("player")->transform->GetPosition() - spawnPos;
			dir /= Vector2Math::Magnitude(dir);

			Actor* enemy = AddActor("enemy");
			enemy->transform->SetPosition(spawnPos);
			enemy->AddComponent<RendererComponent>();
			enemy->AddComponent<Rigidbody>();

			RendererComponent* cachedRenderer = enemy->GetComponent<RendererComponent>();
			cachedRenderer->SetSize(50, 50);
			cachedRenderer->SetTexture("../../../Assets/Textures/Enemy/Enemy_Walk0.png");

			Rigidbody* cachedRigidBody = enemy->GetComponent<Rigidbody>();
			cachedRigidBody->SetRigidbodySettings(1.0f, 0.0f, false);
			cachedRigidBody->SetCurrentVelocity(dir * 50.0f);
			cachedRigidBody->SetAABB();
			cachedRigidBody->SetOnCollide([](void* _enemy) {
				Game::GetCurrentScene()->Find("player")->GetComponent<AudioComponent>()->Play();
				Game::GetCurrentScene()->Destroy(static_cast<Actor*>(_enemy));
				}, enemy);
		}
		spawn_timer = 0.0f;
	}

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
			Vector2 playerCenter = Find("player")->transform->GetPosition();
			Vector2 projectileHalfSize = Vector2(7, 7);

			float x = playerCenter.x + (direction.x * playerHalfSize.x) + (direction.x * projectileHalfSize.x * 1.5f);
			float y = playerCenter.y + (direction.y * playerHalfSize.y) + (direction.y * projectileHalfSize.y * 1.5f);

			Actor* projectile = AddActor("projectile");
			projectile->transform->SetPosition(x, y);
			projectile->AddComponent<RendererComponent>();
			projectile->AddComponent<Rigidbody>();

			RendererComponent* cachedRenderer = projectile->GetComponent<RendererComponent>();
			cachedRenderer->SetSize(projectileHalfSize * 2.0f);
			cachedRenderer->SetTexture("../../../Assets/Textures/projectile.png");

			Rigidbody* cachedRigidBody = projectile->GetComponent<Rigidbody>();
			cachedRigidBody->SetRigidbodySettings(1.0f, 0.0f, false);//static
			cachedRigidBody->SetCurrentVelocity(direction * 100.0f);
			cachedRigidBody->SetAABB();
			cachedRigidBody->SetOnCollide([](void* _projectile) {Game::GetCurrentScene()->Destroy(static_cast<Actor*>(_projectile)); }, projectile);

			//printf("Projectile pos : %f\n", x);

			fire_timer = 0;
		}
	}
#pragma endregion
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
