#pragma once
#include "PhysicsComponentInterface.h"
#include "..\..\Engines\Utils.h"
#include <stdlib.h>

class Rigidbody : public IPhysicsComponent
{
private:
	float m_mass;
	float m_bounciness;
	bool m_obeysGravity;
	Vector2 *m_gravity;
	Vector2 *m_currentVelocity;
	Vector2 *m_maxVelocity;
	bool m_grounded;
	Vector2 *totalFroces;
	
public:
	Rigidbody(float _mass = 1, float _bounciness = 1, bool _obeysGravity = true);

	struct AABB
	{
		Vector2 bLeft;
		Vector2 tRight;
		Vector2 center;
	};

	AABB aabb;

	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Integrate(float dT);
	void GetMass();
	float GetBounciness();
	Vector2 GetCurrentVelocity();
};
