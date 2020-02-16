#pragma once
#include "ActorComponent.h"
#include <SFML/Graphics.hpp>

class RendererComponent : public ActorComponent
{
private:
	sf::Shape* shape;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

	void SetShape(sf::Shape *s);
	sf::Shape* GetShape();

	void SetColor(int r, int g, int b);
	void SetColor(sf::Color color);
	void SetColor(sf::Vector3f color);
};