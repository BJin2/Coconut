#include "Utils.h"
#include <iostream>

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
	using namespace std;
	auto temp = mat.getMatrix();
	float x = temp[12];
	float y = temp[13];
	/*Matrix tempM(1, 2, 3, 
				4, 5, 6, 
				7, 8, 9);
	temp = tempM.getMatrix();
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
			cout << endl;
		cout << temp[i] << ", ";
	}*/
	return Vector2(x, y);
}

Vector2 Vector2Math::ScaleFromMatrix(const Matrix& mat)
{
	auto temp = mat.getMatrix();
	float x = temp[0];
	float y = temp[5];

	return Vector2(x, y);
}