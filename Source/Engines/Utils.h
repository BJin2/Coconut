#pragma once
#include <SFML/Graphics/Transform.hpp>

typedef sf::Vector2f Vector2;
typedef sf::Transform Matrix;

namespace Vector2Math
{
	float Magnitude(Vector2 _a);
	float Dot(Vector2 _a, Vector2 _b);
	Vector2 PositionFromMatrix(const Matrix&);
	Vector2 ScaleFromMatrix(const Matrix&);
}