#include "..\..\Engines\Utils.h"
#include "..\..\Engines\PhysicsEngine.hpp"
#include "Rigidbody.h"
#include "Transform.h"
#include "RendererComponent.h"

Rigidbody::Rigidbody(float _mass, float _bounciness, bool _obeysGravity)
{
	m_mass = _mass;
	m_bounciness = _bounciness;
	m_obeysGravity = _obeysGravity;
	m_gravity = Vector2(0, 9.8f);
	m_maxVelocity = Vector2(10.0f, 10.0f);
	engine = PhysicsEngine::Instance();
	engine->AddRigidBody(this);
	m_grounded = false;
}

void Rigidbody::VStart()
{
	SetAABB();
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
	sf::Shape* shape = GetOwner()->GetComponent<RendererComponent>()->GetShape();
	aabb.bLeft = sf::Vector2f(shape->getGlobalBounds().left, shape->getGlobalBounds().top-shape->getGlobalBounds().height);
	aabb.tRight = Vector2(shape->getGlobalBounds().left+shape->getGlobalBounds().width, shape->getGlobalBounds().top);
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

	Vector2 temp = GetOwner()->transform->GetPosition();
	temp += m_currentVelocity * dt;

	GetOwner()->transform->SetPosition(temp);
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

void Rigidbody::SetRigidbodySettings(float _mass, float _bounciness, bool _obeysGravity)
{
	m_mass = _mass;
	m_bounciness = _bounciness;
	m_obeysGravity = _obeysGravity;
}

void Rigidbody::SetCurrentVelocity(Vector2 v)
{
	m_currentVelocity += v;
}

void Rigidbody::SetMass(float m)
{
	m_mass = m;
}

void Rigidbody::SetBounciness(float b)
{
	m_bounciness = b;
}

Vector2 Rigidbody::GetCurrentVelocity()
{
	return m_currentVelocity;
}
