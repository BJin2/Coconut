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
Transform* Transform::GetChild(int index)
{
	return m_children[index];
}
#pragma region Global
Vector2 Transform::GetPosition()
{
	Matrix mat = m_translationMatrix;
	Transform* p = GetParent();
	while (p)
	{
		mat *= p->GetTranslationMatrix();
		p = GetParent();
	}
	auto temp = mat.getMatrix();
	float x = temp[0];
	float y = temp[4];

	return Vector2(x,y);
}
Vector2 Transform::GetScale()
{
	Matrix mat = m_scaleMatrix;
	Transform* p = GetParent();
	while (p)
	{
		mat *= p->GetScaleMatrix();
		p = GetParent();
	}
	auto temp = mat.getMatrix();
	float x = temp[0];
	float y = temp[4];

	return Vector2(x, y);
}
float4 Transform::GetOrientation()
{
	xmmatrix mat = XMLoadFloat4x4(&m_rotationMatrix);
	Transform* p = GetParent();
	while (p)
	{
		mat *= XMLoadFloat4x4(&p->GetRotationMatrix());
		p = GetParent();
	}
	xmvector quat = XMQuaternionRotationMatrix(mat);
	float4 temp;
	XMStoreFloat4(&temp, quat);
	return temp;
}
float3 Transform::GetRotation()
{
	return QuaternionToEuler(GetOrientation());
}
float4x4 Transform::GetTransform()
{
	xmmatrix mat = XMLoadFloat4x4(&m_localTransformMatrix);
	Transform* p = GetParent();
	while (p)
	{
		mat *= XMLoadFloat4x4(&p->GetLocalTransformMatrix());
		p = GetParent();
	}
	float4x4 temp;
	XMStoreFloat4x4(&temp, mat);
	return temp;
}
#pragma endregion
#pragma region Local
Vector2 Transform::GetLocalPosition()
{
	return m_localPosition;
}
Vector2 Transform::GetLocalScale()
{
	return m_localScale;
}
float Transform::GetLocalRotation()
{
	return angle;
}
Matrix Transform::GetLocalTransform()
{
	return m_localTransformMatrix;
}
Matrix Transform::GetRotationMatrix()
{
	return m_rotationMatrix;
}
Matrix Transform::GetScaleMatrix()
{
	return m_scaleMatrix;
}
Matrix Transform::GetTranslationMatrix()
{
	return m_translationMatrix;
}
Matrix Transform::GetLocalTransformMatrix()
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
void Transform::AddChild(Transform* _child)
{
	m_children.push_back(_child);
}
#pragma region Global
void Transform::SetPosition(const float3& _position)
{
	xmvector position = XMLoadFloat3(&_position);
	xmmatrix mat = XMMatrixTranslationFromVector(position);

	Transform* p = GetParent();
	while (p)
	{
		xmmatrix parentPosition = XMLoadFloat4x4(&p->GetTranslationMatrix());
		xmvector det = XMMatrixDeterminant(parentPosition);
		mat *= XMMatrixInverse(&det, parentPosition);
		p = GetParent();
	}
	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, mat);
	float x = tmp.m[3][0];
	float y = tmp.m[3][1];
	float z = tmp.m[3][2];

	SetLocalPosition(x, y, z);
}
void Transform::SetPosition(float _x, float _y, float _z)
{
	SetPosition(float3(_x, _y, _z));
}
void Transform::SetPosition(const xmvector& _position)
{
	float3 temp;
	XMStoreFloat3(&temp, _position);
	SetPosition(temp);
}
void Transform::SetScale(const float3& _scale)
{
	xmvector scale = XMLoadFloat3(&_scale);
	xmmatrix mat = XMMatrixScalingFromVector(scale);

	Transform* p = GetParent();
	while (p)
	{
		xmmatrix parentScale = XMLoadFloat4x4(&p->GetScaleMatrix());
		xmvector det = XMMatrixDeterminant(parentScale);
		mat *= XMMatrixInverse(&det, parentScale);
		p = GetParent();
	}
	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, mat);
	float x = tmp.m[0][0];
	float y = tmp.m[1][1];
	float z = tmp.m[2][2];

	SetLocalScale(x, y, z);
}
void Transform::SetScale(float _x, float _y, float _z)
{
	SetScale(float3(_x, _y, _z));
}
void Transform::SetScale(const xmvector& _scale)
{
	float3 temp;
	XMStoreFloat3(&temp, _scale);
	SetScale(temp);
}
void Transform::SetOrientation(const float4& _orientation)
{
	xmvector quat = XMLoadFloat4(&_orientation);
	xmmatrix mat = XMMatrixRotationQuaternion(quat);

	Transform* p = GetParent();
	while (p)
	{
		xmmatrix parentRotation = XMLoadFloat4x4(&p->GetRotationMatrix());
		xmvector det = XMMatrixDeterminant(parentRotation);
		mat *= XMMatrixInverse(&det, parentRotation);
		p = GetParent();
	}
	
	quat = XMQuaternionRotationMatrix(mat);
	float4 temp;
	XMStoreFloat4(&temp, quat);
	SetLocalOrientation(temp);
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
void Transform::SetLocalPosition(const Vector2& _position)
{
	m_localPosition = _position;
}

void Transform::SetLocalPosition(float _x, float _y)
{
	m_localPosition = Vector2(_x, _y);
}

void Transform::SetLocalScale(const Vector2& _scale)
{
	m_localScale = _scale;
}

void Transform::SetLocalScale(float _x, float _y)
{
	m_localScale = Vector2(_x, _y);
}

void Transform::SetRotation(float _angle)
{
	angle = _angle;
}
#pragma endregion
#pragma endregion


