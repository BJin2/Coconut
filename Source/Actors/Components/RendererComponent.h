#pragma once
#include "ActorComponent.h"
#include <SFML/Graphics.hpp>

class RendererComponent : public ActorComponent
{
private:
	sf::RectangleShape rect;
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;
	sf::RectangleShape GetRect();
};