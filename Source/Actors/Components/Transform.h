#pragma once
#include "../../Engines/Utils.h"
#include "ActorComponent.h"

class Transform : public ActorComponent
{
private:
	Vector2 m_localPosition;
	Vector2 m_localScale;
	float m_localAngle;
	Matrix m_localTransformMatrix;
	Matrix m_translationMatrix;
	Matrix m_scaleMatrix;
	Matrix m_rotationMatrix;

	Transform* m_parent = nullptr;
	std::vector<Transform*> m_children;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

#pragma region Getters
	Transform* GetParent();
	Transform* GetChild(int index);
#pragma region Global
	Vector2 GetPosition();
	Vector2 GetScale();
	float GetRotation();
	Matrix GetTransform();
	Matrix GetRotationMatrix();
	Matrix GetScaleMatrix();
	Matrix GetTranslationMatrix();
	Matrix GetLocalTransformMatrix();

#pragma endregion
#pragma region Local
	Vector2 GetLocalPosition();
	Vector2 GetLocalScale();
	float GetLocalRotation();
	Matrix GetLocalTransform();
#pragma endregion
#pragma endregion

#pragma region Setters
	void SetParent(Transform* _parent);
	void AddChild(Transform* _child);
#pragma region Global
	void SetPosition(const Vector2& _position);
	void SetPosition(float _x, float _y);

	void SetScale(const Vector2& _scale);
	void SetScale(float _x, float _y);

	void SetRotation(float _angle);
#pragma endregion
#pragma region Local
	void SetLocalPosition(const Vector2& _position);
	void SetLocalPosition(float _x, float _y);

	void SetLocalScale(const Vector2& _scale);
	void SetLocalScale(float _x, float _y);

	void SetLocalRotation(float _angle);
#pragma endregion
#pragma endregion
};
