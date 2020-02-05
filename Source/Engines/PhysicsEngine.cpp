//
//  PhysicsEngine.cpp
//  Engine
//
//  Created by heaseo chung on 2019-10-19.
//  Copyright © 2019 heaseo chung. All rights reserved.
//

#include "PhysicsEngine.hpp"

void PhysicsEngine::AddRigidBody(Rigidbody &_rigidBody)
{
	m_rigidBodies.push_back(_rigidBody);
}

void PhysicsEngine::IntegrateBodies(float dT)
{
	for (auto& rb : m_rigidBodies)
	{
		rb.Integrate(dT);
	}
}

bool PhysicsEngine::IsGrounded(Rigidbody& _rigidBody)
{
	for (auto& rb : m_rigidBodies)
	{
		//TODO CHECK PUT & is right or not.
		if (&rb != &_rigidBody)
		{
			if (_rigidBody.aabb.bLeft.x < rb.aabb.tRight.x
				&& _rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
				&& abs(_rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= m_groundedTol)
			{
				if (abs(_rigidBody.GetCurrentVelocity().y) < m_groundedTol)
					return true;
			}
		}
	}
	return false;
}

void PhysicsEngine::CheckCollision()
{
	for (int i = 0; i < m_rigidBodies.size - 1; i++)
	{
		Rigidbody &bodyA =  m_rigidBodies[i];
		for (int j = i; j < m_rigidBodies.size - i; j++)
		{
			Rigidbody& bodyB = m_rigidBodies[j];

			if (&bodyA != &bodyB)
			{
				//TODO CHECK WHYY CollisionPairt need default Constructor in order to use it in below.
				CollisionPair* pair = new CollisionPair();
				CollisionInfo* colInfo = new CollisionInfo();
				pair->rigidBodyA = bodyA; pair->rigidBodyB = bodyB;

				//TODO Need position
				//Vector2 distance = bodyB.transform.position - bodyA.transform.position;
				//Vector2 halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
				//Vector2 halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;
			}
		}
	}

	for (auto& bodyA : slice(m_rigidBodies, 0, m_rigidBodies.size - 1))
	{

	}
}

void PhysicsEngine::ResolveCollisions()
{
	for (auto& pair : m_collisions)
	{
		float minBounce = min(pair.first.rigidBodyA.GetBounciness(), pair.first.rigidBodyB.GetBounciness());
		//float velAlongNormal = Vector2.Dot(pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal);
	}
}

