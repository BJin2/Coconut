#include "Transform.h"
#include <cmath>

//XMVECTOR T = XMLoadFloat3(&float3);
//XMStoreFloat3(&float3)

//Vector2 a = Vector2(2, 2);
//Matrix translate = Matrix::Identity;
//translate = translate.translate(a);
//a = Vector2Math::PositionFromMatrix(translate);
//printf("%f", a.x);
//printf(", %f", a.y);
//printf("\n");

Transform::Transform()
{
	m_localPosition = Vector2(0.0f, 0.0f);
	m_localScale = Vector2(1.0f, 1.0f);
	m_localAngle = 0.0f;

	m_translationMatrix = Matrix::Identity;
	m_scaleMatrix = Matrix::Identity;
	m_rotationMatrix = Matrix::Identity;
	m_localTransformMatrix = Matrix::Identity;
}

void Transform::VStart()
{
	
}

void Transform::VUpdate(float dt)
{
	m_scaleMatrix = Matrix::Identity;
	m_scaleMatrix.scale(m_localScale);

	m_translationMatrix = Matrix::Identity;
	m_translationMatrix = m_translationMatrix.translate(m_localPosition);

	m_rotationMatrix = Matrix::Identity;
	m_rotationMatrix = m_rotationMatrix.rotate(m_localAngle);

	m_localTransformMatrix = Matrix::Identity * m_scaleMatrix * m_translationMatrix * m_rotationMatrix;
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
		p = p->GetParent();
	}
	return Vector2Math::PositionFromMatrix(mat);
}
Vector2 Transform::GetScale()
{
	Matrix mat = m_scaleMatrix;
	Transform* p = GetParent();
	while (p)
	{
		mat *= p->GetScaleMatrix();
		p = p->GetParent();
	}
	return Vector2Math::ScaleFromMatrix(mat);
}
float Transform::GetRotation()
{
	Matrix mat = m_rotationMatrix;
	Transform* p = GetParent();
	while (p)
	{
		mat *= p->GetRotationMatrix();
		p = p->GetParent();
	}
	auto temp = mat.getMatrix();
	return acos(temp[0]);
}
Matrix Transform::GetTransform()
{
	Matrix mat = m_localTransformMatrix;
	Transform* p = GetParent();
	while (p)
	{
		mat *= p->GetLocalTransformMatrix();
		p = p->GetParent();
	}
	return mat;
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
	return m_localAngle;
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
	m_parent->AddChild(this);
}
void Transform::AddChild(Transform* _child)
{
	auto it = std::find(m_children.begin(), m_children.end(), _child);
	if (it != m_children.end())
		return;

	if(_child->GetParent() != this)
		_child->SetParent(this);
	m_children.push_back(_child);
}
#pragma region Global
void Transform::SetPosition(const Vector2& _position)
{
	Matrix mat = Matrix::Identity;
	mat = mat.translate(_position);

	Transform* p = GetParent();
	while (p)
	{
		Matrix inverseParentTranslation = (p->GetTranslationMatrix()).getInverse();
		mat *= inverseParentTranslation;
		p = p->GetParent();
	}

	SetLocalPosition(Vector2Math::PositionFromMatrix(mat));
}
void Transform::SetPosition(float _x, float _y)
{
	SetPosition(Vector2(_x, _y));
}

void Transform::SetScale(const Vector2& _scale)
{
	Matrix mat = Matrix::Identity;
	mat = mat.scale(_scale);

	Transform* p = GetParent();
	while (p)
	{
		Matrix inverseParentScale = (p->GetScaleMatrix()).getInverse();
		mat *= inverseParentScale;
		p = p->GetParent();
	}

	SetLocalScale(Vector2Math::ScaleFromMatrix(mat));
}
void Transform::SetScale(float _x, float _y)
{
	SetScale(Vector2(_x, _y));
}
void Transform::SetRotation(float _angle)
{
	Matrix mat = Matrix::Identity;
	mat = mat.rotate(_angle);
	Transform* p = GetParent();
	while (p)
	{
		Matrix inverseParentRotation = (p->GetRotationMatrix()).getInverse();
		mat *= inverseParentRotation;
		p = p->GetParent();
	}
	auto temp = mat.getMatrix();
	printf("Radian : %f\n", acos(temp[0]));
	float angle = Vector2Math::RadianToDegree(acos(temp[0]));
	printf("Angle : %f\n",angle);
	SetLocalRotation(angle);
}

#pragma endregion
#pragma region Local
void Transform::SetLocalPosition(const Vector2& _position)
{
	m_localPosition = _position;
	m_translationMatrix = Matrix::Identity;
	m_translationMatrix = m_translationMatrix.translate(m_localPosition);
}

void Transform::SetLocalPosition(float _x, float _y)
{
	SetLocalPosition(Vector2(_x, _y));
}

void Transform::SetLocalScale(const Vector2& _scale)
{
	m_localScale = _scale;
	m_scaleMatrix = Matrix::Identity;
	m_scaleMatrix.scale(m_localScale);
}

void Transform::SetLocalScale(float _x, float _y)
{
	SetLocalScale(Vector2(_x, _y));
}

void Transform::SetLocalRotation(float _angle)
{
	m_localAngle = _angle;
	m_rotationMatrix = Matrix::Identity;
	m_rotationMatrix = m_rotationMatrix.rotate(m_localAngle);
}
#pragma endregion
#pragma endregion


