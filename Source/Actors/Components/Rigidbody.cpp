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

void Rigidbody::VStart()
{
}

void Rigidbody::VUpdate(float delta)
{
}

void Rigidbody::Stop()
{
	m_currentVelocity = new Vector2(0, 0);
	totalFroces = new Vector2(0, 0);
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
	Vector2* acceleration = new Vector2();

	if (m_obeysGravity && !IsGrounded())
	{
		acceleration = m_gravity;
	}
	else
	{
		if (abs(m_currentVelocity->y) < 0.05f) m_currentVelocity->y = 0;
	}
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
	return *m_currentVelocity;
}
