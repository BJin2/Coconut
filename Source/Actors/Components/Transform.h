#pragma once
#include <DirectXMath.h>
#include "ActorComponent.h"

typedef DirectX::XMFLOAT3 float3;
typedef DirectX::XMFLOAT4 float4;
typedef DirectX::XMVECTOR xmvector;
typedef DirectX::XMFLOAT4X4 float4x4;
typedef DirectX::XMMATRIX xmmatrix;

class Transform : public ActorComponent
{
private:
	float3 m_localPosition;
	float3 m_localScale;
	float4 m_localOrientation;

	float4x4 m_translationMatrix;
	float4x4 m_scaleMatrix;
	float4x4 m_rotationMatrix;

	float4x4 m_localTransformMatrix;

	Transform* m_parent = nullptr;
	std::vector<Transform*> m_children;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

#pragma region Getters
	Transform* GetParent();
	Transform* GetChild(int index);
#pragma region Global
	float3 GetPosition();
	float3 GetScale();
	float4 GetOrientation();
	float3 GetRotation();
	float4x4 GetTransform();
	float4x4 GetRotationMatrix();
	float4x4 GetScaleMatrix();
	float4x4 GetTranslationMatrix();
	float4x4 GetLocalTransformMatrix();

#pragma endregion
#pragma region Local
	float3 GetLocalPosition();
	float3 GetLocalScale();
	float4 GetLocalOrientation();
	float3 GetLocalRotation();
	float4x4 GetLocalTransform();
#pragma endregion
#pragma endregion

#pragma region Setters
	void SetParent(Transform* _parent);
	void AddChild(Transform* _child);
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
