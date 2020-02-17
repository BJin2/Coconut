//
//  PhysicsEngine.cpp
//  Engine
//
//  Created by heaseo chung on 2019-10-19.
//  Copyright © 2019 heaseo chung. All rights reserved.
//
#include "..\Engines\Utils.h"
#include "PhysicsEngine.hpp"
#include "..\Actors\Components\Rigidbody.h"
#include "../Actors/Components/Transform.h"

PhysicsEngine* PhysicsEngine::instance;

PhysicsEngine* PhysicsEngine::Instance()
{
	if (instance)
		return instance;
	return instance = new PhysicsEngine();
}

void PhysicsEngine::AddRigidBody(Rigidbody* _rigidBody)
{
	m_rigidBodies.push_back(_rigidBody);
}

void PhysicsEngine::IntegrateBodies(float dt)
{
	for (auto rb : m_rigidBodies)
	{
		rb->Integrate(dt);
	}
}

bool PhysicsEngine::IsGrounded(Rigidbody* _rigidBody)
{
	for (auto rb : m_rigidBodies)
	{
		if (rb != _rigidBody)
		{
			if (_rigidBody->aabb.bLeft.x < rb->aabb.tRight.x
				&& _rigidBody->aabb.tRight.x > rb->aabb.bLeft.x
				&& abs(_rigidBody->aabb.bLeft.y - rb->aabb.tRight.y) <= m_groundedTol)
			{
				if (abs(_rigidBody->GetCurrentVelocity().y) < m_groundedTol)
					return true;
			}
		}
	}
	return false;
}

void PhysicsEngine::CheckCollision()
{
	std::map<CollisionPair*, CollisionInfo*>::key_compare compare = m_collisions.key_comp();
	for (int i = 0; i < m_rigidBodies.size() - 1; i++)
	{
		Rigidbody* bodyA =  m_rigidBodies[i];
		for (int j = i; j < m_rigidBodies.size() - i; j++)
		{
			Rigidbody* bodyB = m_rigidBodies[j];

			if (bodyA != bodyB)
			{
				CollisionPair* pair = new CollisionPair();
				CollisionInfo* colInfo = new CollisionInfo();
				pair->rigidBodyA = bodyA; pair->rigidBodyB = bodyB;
				auto search = m_collisions.find(pair);

				Vector2 distance = bodyB->GetOwner()->transform->GetPosition() - bodyA->GetOwner()->transform->GetPosition();
				Vector2 halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2.0f;
				Vector2 halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2.0f;
				Vector2 gap = Vector2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				if (gap.x < 0 && gap.y < 0)
				{
					if (search != m_collisions.end())
					{
						m_collisions.erase(pair);
					}

					if (gap.x > gap.y)
					{
						if(distance.x > 0)
							colInfo->collisionNormal = Vector2(1, 0);
						else
							colInfo->collisionNormal = Vector2(-1, 0);
						colInfo->penetration = gap.x;
					}
					else
					{
						if(distance.y > 0)
							colInfo->collisionNormal = Vector2(0, 1);
						else
							colInfo->collisionNormal = Vector2(0, -1);
						colInfo->penetration = gap.y;
					}
					m_collisions.insert(std::pair<CollisionPair*, CollisionInfo*>(pair, colInfo));
				}
				else if (search != m_collisions.end())
				{
					m_collisions.erase(pair);
				}
			}
		}
	}
}

void PhysicsEngine::ResolveCollisions()
{
	for (std::map<CollisionPair*, CollisionInfo*>::iterator pair = m_collisions.begin(); pair != m_collisions.end(); ++pair)
	{
		float minBounce = min(pair->first->rigidBodyA->GetBounciness(), pair->first->rigidBodyB->GetBounciness());
		float velAlongNormal = Vector2Math::Dot(pair->first->rigidBodyB->GetCurrentVelocity() - pair->first->rigidBodyA->GetCurrentVelocity(), pair->second->collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (pair->first->rigidBodyA->GetMass() == 0)
			invMassA = 0;
		else
			invMassA = 1 / pair->first->rigidBodyA->GetMass();

		if (pair->first->rigidBodyB->GetMass() == 0)
			invMassB = 0;
		else
			invMassB = 1 / pair->first->rigidBodyB->GetMass();

		j /= invMassA + invMassB;

		Vector2 impulse = j * m_collisions[pair->first]->collisionNormal;

		if (pair->first->rigidBodyA->GetMass() != 0)
			pair->first->rigidBodyA->SetCurrentVelocity(-1 / pair->first->rigidBodyA->GetMass() * impulse);
		if (pair->first->rigidBodyB->GetMass() != 0)
			pair->first->rigidBodyB->SetCurrentVelocity(1 / pair->first->rigidBodyA->GetMass() * impulse);

		if (abs(m_collisions[pair->first]->penetration > 0.01f))
		{
			PositionalCorrection(pair->first);
		}
	}
}

void PhysicsEngine::PositionalCorrection(CollisionPair* c)
{
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c->rigidBodyA->GetMass() == 0)
		invMassA = 0;
	else
		invMassA = 1 / c->rigidBodyA->GetMass();

	if (c->rigidBodyB->GetMass() == 0)
		invMassB = 0;
	else
		invMassB = 1 / c->rigidBodyB->GetMass();

	Vector2 correction = ((m_collisions[c]->penetration / (invMassA + invMassB)) * percent) * -m_collisions[c]->collisionNormal;

	Vector2 temp = c->rigidBodyA->transform->GetPosition();
	temp -= invMassA * correction;
	c->rigidBodyA->transform->SetPosition(temp);

	temp = c->rigidBodyB->transform->GetPosition();
	temp += invMassB * correction;
	c->rigidBodyB->transform->SetPosition(temp);
}

void PhysicsEngine::UpdatePhysics(float dt)
{
	IntegrateBodies(dt);
	CheckCollision();
	ResolveCollisions();
}

