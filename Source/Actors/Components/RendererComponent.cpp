#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"

void RendererComponent::VStart()
{
	GraphicEngine::Instance()->RegisterRenderTarget(this);
	rect = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(-2);
}

void RendererComponent::VUpdate(float dt)
{
}

sf::RectangleShape RendererComponent::GetRect()
{
	return rect;
}
