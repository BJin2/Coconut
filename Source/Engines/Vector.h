#pragma once
#include <DirectXMath.h>

typedef DirectX::XMFLOAT2 float2;
typedef DirectX::XMFLOAT3 float3;
typedef DirectX::XMFLOAT4 float4;
typedef DirectX::XMVECTOR xmvector;
typedef DirectX::XMFLOAT4X4 float4x4;
typedef DirectX::XMMATRIX xmmatrix;

class Vector2
{
private:
	float2 vec2;

public:
	Vector2();
	Vector2(float x, float y);
	void X(float x);
	void Y(float y);
	float X();
	float Y();
	float Magnitude();

	static float Dot(Vector2 a, Vector2 b);
};