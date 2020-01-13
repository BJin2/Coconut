#include "Transform.h"
#include <DirectXPackedVector.h>

using namespace DirectX;

//XMVECTOR T = XMLoadFloat3(&float3);
//XMStoreFloat3(&float3)
void Transform::VStart()
{
}

void Transform::VUpdate(float dt)
{
	xmmatrix scale = XMMatrixScalingFromVector(XMLoadFloat3(&m_localScale));
	XMStoreFloat4x4(&m_scaleMatrix, scale);
	xmmatrix translation = XMMatrixTranslationFromVector(XMLoadFloat3(&m_localPosition));
	XMStoreFloat4x4(&m_translationMatrix, translation);
	xmmatrix rotation = XMMatrixRotationQuaternion(XMLoadFloat4(&m_localOrientation));
	XMStoreFloat4x4(&m_rotationMatrix, rotation);

	xmmatrix transform = scale * translation * rotation;
	XMStoreFloat4x4(&m_localTransformMatrix, transform);
}

#pragma region Getters
Transform* Transform::GetParent()
{
	return m_parent;
}
#pragma region Global
float3 Transform::GetPosition()
{
	return m_position;
}
float3 Transform::GetScale()
{
	return m_scale;
}
float4 Transform::GetOrientation()
{
	return m_orientation;
}
float3 Transform::GetRotation()
{
	//TODO implement  quaternion -> vector

	return float3();
}
float4x4 Transform::GetTransform()
{
	return m_transformMatrix;
}
#pragma endregion
#pragma region Local
float3 Transform::GetLocalPosition()
{
	return m_localPosition;
}
float3 Transform::GetLocalScale()
{
	return m_localScale;
}
float4 Transform::GetLocalOrientation()
{
	return m_localOrientation;
}
float3 Transform::GetLocalRotation()
{
	//TODO implement vector -> quaternion
	return float3();
}
float4x4 Transform::GetLocalTransform()
{
	return m_localTransformMatrix;
}
#pragma endregion
#pragma endregion

#pragma region Setters
void Transform::SetParent(Transform* _parent)
{
	m_parent = _parent;
}
#pragma region Global
void Transform::SetPosition(const float3& _position)
{
	m_position = _position;
	//TODO update local position
}
void Transform::SetPosition(float _x, float _y, float _z)
{
	SetPosition(float3(_x, _y, _z));
}
void Transform::SetPosition(const xmvector& _position)
{
	XMStoreFloat3(&m_position, _position);
}
void Transform::SetScale(const float3& _scale)
{
	m_scale = _scale;
	//TODO update local scale
}
void Transform::SetScale(float _x, float _y, float _z)
{
	SetScale(float3(_x, _y, _z));
}
void Transform::SetScale(const xmvector& _scale)
{
	float3 temp;
	XMStoreFloat3(&temp, _scale);
	XMStoreFloat3(&m_scale, _scale);
}
void Transform::SetOrientation(const float4& _orientation)
{
	m_orientation = _orientation;
	//TODO update local orientation
}
void Transform::SetOrientation(float _x, float _y, float _z, float _w)
{
	SetOrientation(float4(_x, _y, _z, _w));
}
void Transform::SetOrientation(const xmvector& _orientation)
{
	float4 temp;
	XMStoreFloat4(&temp, _orientation);
	SetOrientation(temp);
}
void Transform::SetRotation(const float3& _rotation)
{
	//TODO float3 -> quaternion
	xmvector quat = XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&_rotation));
	SetOrientation(quat);
}
void Transform::SetRotation(float _x, float _y, float _z)
{
	SetRotation(float3(_x, _y, _z));
}
void Transform::SetRotation(const xmvector& _rotation)
{
	float3 temp;
	XMStoreFloat3(&temp, _rotation);
	SetRotation(temp);
}
#pragma endregion
#pragma region Local
void Transform::SetLocalPosition(const float3& _position)
{
	m_localPosition = _position;
}
void Transform::SetLocalPosition(float _x, float _y, float _z)
{
	SetLocalPosition(float3(_x, _y, _z));
}
void Transform::SetLocalPosition(const xmvector& _position)
{
	float3 temp;
	XMStoreFloat3(&temp, _position);
	SetLocalPosition(temp);
}
void Transform::SetLocalScale(const float3& _scale)
{
	m_localScale = _scale;
}
void Transform::SetLocalScale(float _x, float _y, float _z)
{
	SetLocalScale(float3(_x, _y, _z));
}
void Transform::SetLocalScale(const xmvector& _scale)
{
	float3 temp;
	XMStoreFloat3(&temp, _scale);
	SetLocalScale(temp);
}
void Transform::SetLocalOrientation(const float4& _orientation)
{
	m_localOrientation = _orientation;
	//update global orientation
}
void Transform::SetLocalOrientation(float _x, float _y, float _z, float _w)
{
	SetLocalOrientation(float4(_x, _y, _z, _w));
}
void Transform::SetLocalOrientation(const xmvector& _orientation)
{
	float4 temp;
	XMStoreFloat4(&temp, _orientation);
	SetLocalOrientation(temp);
}
void Transform::SetLocalRotation(const float3& _rotation)
{
	//TODO float3 to quaternion
}
void Transform::SetLocalRotation(float _x, float _y, float _z)
{
	SetLocalRotation(float3(_x, _y, _z));
}
void Transform::SetLocalRotation(const xmvector& _rotation)
{
	float3 temp;
	XMStoreFloat3(&temp, _rotation);
	SetLocalRotation(temp);
}
#pragma endregion
#pragma endregion

