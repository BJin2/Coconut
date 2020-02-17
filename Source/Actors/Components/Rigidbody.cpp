#include "..\..\Engines\Utils.h"
#include "Rigidbody.h"
#include "..\..\Engines\PhysicsEngine.hpp"
#include "..\Components\Transform.h"

Rigidbody::Rigidbody(float _mass, float _bounciness, bool _obeysGravity)
{
	m_mass = _mass;
	m_bounciness = _bounciness;
	m_obeysGravity = _obeysGravity;
	m_gravity = Vector2(0, -9.8f);
	m_maxVelocity = Vector2(10.0f, 10.0f);
	transform = this->GetOwner()->transform;
	engine = new PhysicsEngine();
	m_grounded = false;
}

void Rigidbody::VStart()
{
	SetAABB();
	engine->AddRigidBody(this);
}

void Rigidbody::VUpdate(float delta)
{
}

void Rigidbody::AddForce(Vector2 force)
{
	totalForces += force;
}

void Rigidbody::Stop()
{
	m_currentVelocity = Vector2(0, 0);
	totalForces = Vector2(0, 0);
}

bool Rigidbody::IsGrounded()
{
	m_grounded = engine->IsGrounded(this);
	return false;
}

void Rigidbody::SetAABB()
{
}

void Rigidbody::Integrate(float dt)
{
	Vector2 acceleration = Vector2(0, 0);

	if (m_obeysGravity && !IsGrounded())
	{
		acceleration = m_gravity;
	}
	else
	{
		if (abs(m_currentVelocity.y) < 0.05f) m_currentVelocity.y = 0;
	}

	acceleration += totalForces / m_mass;
	if (m_mass == 0)
		acceleration = Vector2Math::Zero();

	m_currentVelocity += acceleration * dt;

	Vector2 temp = transform->GetPosition();
	temp += m_currentVelocity * dt;

	transform->SetPosition(temp);
	SetAABB();

	totalForces = Vector2Math::Zero();
}

float Rigidbody::GetMass()
{
	return m_mass;
}

float Rigidbody::GetBounciness()
{
	return m_bounciness;
}

void Rigidbody::SetCurrentVelocity(Vector2 v)
{
	m_currentVelocity += v;
}

Vector2 Rigidbody::GetCurrentVelocity()
{
	return m_currentVelocity;
}
