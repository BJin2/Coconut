#include "Vector.h"

using namespace DirectX;
//XMVECTOR T = XMLoadFloat3(&float3);
//XMStoreFloat3(&float3)

Vector2::Vector2()
{
	vec2 = float2(0.0f, 0.0f);
}

Vector2::Vector2(float x, float y)
{
	vec2 = float2(x, y);
}

void Vector2::X(float x)
{
	vec2.x = x;
}

void Vector2::Y(float y)
{
	vec2.y = y;
}

float Vector2::X()
{
	return vec2.x;
}

float Vector2::Y()
{
	return vec2.y;
}

float Vector2::Magnitude()
{
	xmvector vec = XMLoadFloat2(&vec2);
	vec = XMVector2Length(vec);
	float2 temp;
	XMStoreFloat2(&temp, vec);
	return temp.x;
}

float Vector2::Dot(Vector2 _a, Vector2 _b)
{
	float2 a = float2(_a.X(), _a.Y());
	xmvector vec1 = XMLoadFloat2(&a);

	float2 b = float2(_b.X(), _b.Y());
	xmvector vec2 = XMLoadFloat2(&b);

	xmvector result = XMVector2Dot(vec1, vec2);

	float2 resultFloat2;
	XMStoreFloat2(&resultFloat2, result);

	return resultFloat2.x;
}
