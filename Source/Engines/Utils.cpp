#include "Utils.h"

float Vector2Math::Magnitude(Vector2 _a)
{
	return 0.0f;
}

float Vector2Math::Dot(Vector2 _a, Vector2 _b)
{
	return 0.0f;
}

Vector2 Vector2Math::PositionFromMatrix(const Matrix& mat)
{
	auto temp = mat.getMatrix();
	float x = temp[6];
	float y = temp[7];

	return Vector2(x, y);
}

Vector2 Vector2Math::ScaleFromMatrix(const Matrix& mat)
{
	auto temp = mat.getMatrix();
	float x = temp[0];
	float y = temp[4];

	return Vector2(x, y);
}