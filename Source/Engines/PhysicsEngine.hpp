#ifndef PhysicsEngine_hpp
#define PhysicsEngine_hpp
#include "..\Actors\Components\Rigidbody.h"
#include "..\Engines\Utils.h"
#include <map>
#include <stdlib.h>  
#include <algorithm> 

using namespace std;

class PhysicsEngine
{
public:
	struct CollisionPair
	{
		CollisionPair();
		Rigidbody &rigidBodyA;
		Rigidbody &rigidBodyB;
	};

	struct CollisionInfo
	{
		Vector2 collisionNormal;
		float penetration;
	};

	void AddRigidBody(Rigidbody &_rigidBody);
	void IntegrateBodies(float dT);
	bool IsGrounded(Rigidbody &_rigidBody);
	void CheckCollision();
	void ResolveCollisions();
	void PositionalCorrection();
	void UpdatePhysics();
	void FixedUpdate();

	template<typename T>
	std::vector<T> slice(std::vector<T> const& v, int m, int n);
private:
	float m_groundedTol;
	map<CollisionPair, CollisionInfo> m_collisions;
	vector<Rigidbody> m_rigidBodies;
};


#endif /* PhysicsEngine_hpp */

template<typename T>
inline std::vector<T> PhysicsEngine::slice(std::vector<T> const& v, int m, int n)
{
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n + 1;

	std::vector<T> vec(first, last);
	return vec;
}
