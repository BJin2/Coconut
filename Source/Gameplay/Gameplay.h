#pragma once
#include "../Engines/Scene.h"
#include "../Engines/Game.h"
#include "../Engines/GraphicEngine.hpp"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"
#include "../../Engines/InputCommand.hpp"

#pragma region Temporary variables
//temporary variables. Will be moved to script
float fire_timer = 0;
float spawn_timer = 0;
sf::Vector2f direction = Vector2(0, 1);
std::string spawner_direction[4] = { "east", "south", "west", "north" };
bool gameover = false;
#pragma endregion

void GameplayStart()
{
#pragma region Hard coded game logic
	Scene* currentScene = Game::GetCurrentScene();
	currentScene->Find("bgm")->GetComponent<AudioComponent>()->Play();
	currentScene->Find("player")->GetComponent<Rigidbody>()->SetOnCollide([](void* _player) {
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
		}, currentScene->Find("player"));
#pragma endregion
}

void GameplayUpdate(float delta)
{
#pragma region Hard coded game logic
	if (gameover)
		return;

	Scene* currentScene = Game::GetCurrentScene();

	fire_timer += delta;
	spawn_timer += delta;
	if (spawn_timer >= 3.0f)
	{
		Vector2 dir = Vector2(0, 0);
		for (int i = 0; i < 4; i++)
		{
			Vector2 spawnPos = currentScene->Find(spawner_direction[i])->transform->GetPosition();
			dir = currentScene->Find("player")->transform->GetPosition() - spawnPos;
			dir /= Vector2Math::Magnitude(dir);

			Actor* enemy = currentScene->AddActor("enemy");
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
		currentScene->Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Right.png");
		direction = Vector2(1, 0);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::A))
	{
		//Find("player")->transform->Translate(Vector2(-1, 0), 3 * delta);
		currentScene->Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Left.png");
		direction = Vector2(-1, 0);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::W))
	{
		//Find("player")->transform->Translate(Vector2(0, 1), 3 * delta);
		currentScene->Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Up.png");
		direction = Vector2(0, -1);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::S))
	{
		//Find("player")->transform->Translate(Vector2(0, -1), 3 * delta);
		currentScene->Find("player")->GetComponent<RendererComponent>()->SetTexture("../../../Assets/Textures/Player/Player_Down.png");
		direction = Vector2(0, 1);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::Space))
	{
		if (fire_timer >= 0.2f)
		{
			Vector2 playerHalfSize = currentScene->Find("player")->GetComponent<RendererComponent>()->GetSize() * 0.5f;
			Vector2 playerCenter = currentScene->Find("player")->transform->GetPosition();
			Vector2 projectileHalfSize = Vector2(7, 7);

			float x = playerCenter.x + (direction.x * playerHalfSize.x) + (direction.x * projectileHalfSize.x * 1.5f);
			float y = playerCenter.y + (direction.y * playerHalfSize.y) + (direction.y * projectileHalfSize.y * 1.5f);

			Actor* projectile = currentScene->AddActor("projectile");
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