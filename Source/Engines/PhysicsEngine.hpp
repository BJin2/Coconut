#pragma once
#include <map>
#include <vector>
#include <stdlib.h>  
#include <algorithm> 

using namespace std;

class Rigidbody;

class PhysicsEngine
{
public:
	struct CollisionPair
	{
		Rigidbody* rigidBodyA;
		Rigidbody* rigidBodyB;
	};

	struct CollisionInfo
	{
		Vector2 collisionNormal;
		float penetration;
	};

	void AddRigidBody(Rigidbody* _rigidBody);
	void IntegrateBodies(float dt);
	bool IsGrounded(Rigidbody* _rigidBody);
	void CheckCollision();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair* c);
	void UpdatePhysics(float dt);

private:
	float m_groundedTol;
	map<CollisionPair*, CollisionInfo*> m_collisions;
	vector<Rigidbody*> m_rigidBodies;
};
