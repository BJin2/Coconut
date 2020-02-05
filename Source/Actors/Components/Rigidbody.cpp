#include "Rigidbody.h"

Rigidbody::Rigidbody(float _mass, float _bounciness, bool _obeysGravity)
{
	m_mass = _mass;
	m_bounciness = _bounciness;
	m_obeysGravity = _obeysGravity;
	m_gravity = new Vector2(0, -9.8f);
	m_maxVelocity = new Vector2(10.0f, 10.0f);
	m_grounded = false;
}

void Rigidbody::Stop()
{
}

bool Rigidbody::IsGrounded()
{
	return false;
}

void Rigidbody::SetAABB()
{
}

void Rigidbody::Integrate(float dT)
{
}

void Rigidbody::GetMass()
{
}

float Rigidbody::GetBounciness()
{
	return m_bounciness;
}

Vector2 Rigidbody::GetCurrentVelocity()
{
	return m_currentVelocity;
}
