#pragma once
#include "ActorComponent.h"
#include <string>
#include <SFML/Graphics.hpp>

class RendererComponent : public ActorComponent
{
private:
	sf::Shape* shape;
	sf::Texture *texture;
	sf::Vector2f size;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

	void SetShape(sf::Shape *s);
	void SetColor(int r, int g, int b);
	void SetColor(sf::Color color);
	void SetTexture(std::string textureFile);
	void SetSize(sf::Vector2f _size);
	
	sf::Shape* GetShape() { return shape; };
	sf::Color GetColor() { return shape->getFillColor(); }
	sf::Vector2f GetSize() { return size; }
};