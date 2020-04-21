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

PhysicsEngine::PhysicsEngine()
{
	m_groundedTol = 0.5f;
	m_rigidBodies.clear();
	m_collisions.clear();
}

PhysicsEngine::~PhysicsEngine()
{
	m_rigidBodies.clear();
	for (auto c : m_collisions)
	{
		if (c.first)
			delete c.first;
		if (c.second)
			delete c.second;
	}
	m_collisions.clear();
}

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

bool PhysicsEngine::DestroyRigidBody(Rigidbody* _rigidBody)
{
	bool result = false;
	for (auto rigidBody = m_rigidBodies.begin(); rigidBody != m_rigidBodies.end();)
	{
		if (*rigidBody == _rigidBody)
		{
			rigidBody = m_rigidBodies.erase(rigidBody);
			result = true;
			break;
		}
		else
		{
			rigidBody++;
		}
	}

	for (auto collision = m_collisions.begin(); collision != m_collisions.end();)
	{
		if ((collision->first->rigidBodyA == _rigidBody) ||
			(collision->first->rigidBodyB == _rigidBody))
		{
			collision = m_collisions.erase(collision);
			result = true;
		}
		else
		{
			collision++;
		}
	}


	return result;
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

bool TestAABBOverlap(Rigidbody* a, Rigidbody* b)
{
	float d1x = b->aabb.bLeft.x - a->aabb.tRight.x;
	float d1y = b->aabb.bLeft.y - a->aabb.tRight.y;
	float d2x = a->aabb.bLeft.x - b->aabb.tRight.x;
	float d2y = a->aabb.bLeft.y - b->aabb.tRight.y;
	if (d1x > 0.0f || d1y > 0.0f)
		return false;
	if (d2x > 0.0f || d2y > 0.0f)
		return false;
	return true;
}

void PhysicsEngine::CheckCollision()
{
	if (m_rigidBodies.size() == 0)
		return;

	for (int i = 0; i < m_rigidBodies.size(); i++)
	{
		Rigidbody* bodyA =  m_rigidBodies[i];

		for (int j = 0; j < m_rigidBodies.size(); j++)
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
					for (auto c : m_collisions)
					{
						if (c.first->rigidBodyA == pair->rigidBodyA &&
							c.first->rigidBodyB == pair->rigidBodyB)
						{
							m_collisions.erase(pair);
						}
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
				else
				{
					for (auto c : m_collisions)
					{
						if (c.first->rigidBodyA == pair->rigidBodyA &&
							c.first->rigidBodyB == pair->rigidBodyB)
						{
							m_collisions.erase(pair);
						}
					}
					delete pair;
					delete colInfo;
				}
			}
		}
	}
}

void PhysicsEngine::ResolveCollisions()
{
	for (std::map<CollisionPair*, CollisionInfo*>::iterator pair = m_collisions.begin(); pair != m_collisions.end(); ++pair)
	{
		if (!pair->first->rigidBodyA ||
			!pair->first->rigidBodyB)
			continue;

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

		pair->first->rigidBodyA->SetCurrentVelocity(-impulse*invMassA);
		pair->first->rigidBodyA->OnCollide();
		pair->first->rigidBodyB->SetCurrentVelocity(impulse * invMassB);
		pair->first->rigidBodyB->OnCollide();

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

	Vector2 temp = c->rigidBodyA->GetOwner()->transform->GetPosition();
	temp -= invMassA * correction;
	c->rigidBodyA->GetOwner()->transform->SetPosition(temp);

	temp = c->rigidBodyB->GetOwner()->transform->GetPosition();
	temp += invMassB * correction;
	c->rigidBodyB->GetOwner()->transform->SetPosition(temp);
}

void PhysicsEngine::UpdatePhysics(float dt)
{
	IntegrateBodies(dt);
	CheckCollision();
	ResolveCollisions();
}

