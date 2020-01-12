#pragma once
#include <DirectXMath.h>
#include "ActorComponent.h"

typedef DirectX::XMFLOAT3 float3;
typedef DirectX::XMFLOAT4 float4;
typedef DirectX::XMVECTOR xmvector;
typedef DirectX::XMFLOAT4X4 matrix4;
typedef DirectX::XMMATRIX xmmatrix;

class Transform : public ActorComponent
{
private:
	float3 m_position;
	float3 m_scale;
	float4 m_orientation;
	
	float3 m_localPosition;
	float3 m_localScale;
	float4 m_localOrientation;

	matrix4 m_translationMatrix;
	matrix4 m_scaleMatrix;
	matrix4 m_rotationMatrix;

	matrix4 m_transformMatrix;
	matrix4 m_localTransformMatrix;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

#pragma region Getters
#pragma region Global
	float3 GetPosition();
	float3 GetScale();
	float4 GetOrientation();
	float3 GetRotation();
	matrix4 GetTransform();
#pragma endregion
#pragma region Local
	float3 GetLocalPosition();
	float3 GetLocalScale();
	float4 GetLocalOrientation();
	float3 GetLocalRotation();
	matrix4 GetLocalTransform();
#pragma endregion
#pragma endregion

#pragma region Setters
#pragma region Global
	void SetPosition(const float3& _position);
	void SetPosition(float _x, float _y, float _z);
	void SetPosition(const xmvector& _position);

	void SetScale(const float3& _scale);
	void SetScale(float _x, float _y, float _z);
	void SetScale(const xmvector& _scale);

	void SetOrientation(const float4& _orientation);
	void SetOrientation(float _x, float _y, float _z, float _w);
	void SetOrientation(const xmvector& _orientation);

	void SetRotation(const float3& _rotation);
	void SetRotation(float _x, float _y, float _z);
	void SetRotation(const xmvector& _rotation);
#pragma endregion
#pragma region Local
	void SetLocalPosition(const float3& _position);
	void SetLocalPosition(float _x, float _y, float _z);
	void SetLocalPosition(const xmvector& _position);

	void SetLocalScale(const float3& _scale);
	void SetLocalScale(float _x, float _y, float _z);
	void SetLocalScale(const xmvector& _scale);

	void SetLocalOrientation(const float4& _orientation);
	void SetLocalOrientation(float _x, float _y, float _z, float _w);
	void SetLocalOrientation(const xmvector& _orientation);

	void SetLocalRotation(const float3& _rotation);
	void SetLocalRotation(float _x, float _y, float _z);
	void SetLocalRotation(const xmvector& _rotation);
#pragma endregion
#pragma endregion

};
