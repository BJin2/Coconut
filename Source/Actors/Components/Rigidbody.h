#pragma once
#include "ActorComponent.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class Transform;
class PhysicsEngine;

class Rigidbody : public ActorComponent
{
private:
	float m_mass;
	float m_bounciness;
	bool m_obeysGravity;
	Vector2 m_gravity;
	Vector2 m_currentVelocity;
	Vector2 m_maxVelocity;
	bool m_grounded;
	Vector2 totalForces;
	
public:
	PhysicsEngine *engine;

	Rigidbody(float _mass = 1, float _bounciness = 0.8f, bool _obeysGravity = false);

	struct AABB
	{
		Vector2 bLeft;
		Vector2 tRight;
		Vector2 center;
	} aabb;

	virtual void VStart() override;
	virtual void VUpdate(float delta) override;

	void AddForce(Vector2 force);
	void Stop();
	bool IsGrounded();
	void Integrate(float dt);
	void SetAABB();
	void SetRigidbodySettings(float _mass = 1, float _bounciness = 0.8f, bool _obeysGravity = false);
	void SetCurrentVelocity(Vector2 v);
	void SetMass(float m);
	void SetBounciness(float b);
	Vector2 GetCurrentVelocity();
	float GetMass();
	float GetBounciness();
};
