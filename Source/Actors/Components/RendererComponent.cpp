#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"

void RendererComponent::VStart()
{
	GraphicEngine::Instance()->RegisterRenderTarget(this);
	SetShape(new sf::RectangleShape(sf::Vector2f(100.0f, 100.0f)));
	//SetSize(100, 100);
	//rect = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	shape->setOrigin(shape->getScale().x / 2, shape->getScale().y / 2);
	SetColor(sf::Color::Black);
}

void RendererComponent::VUpdate(float dt)
{

}

void RendererComponent::SetShape(sf::Shape* s)
{
	shape = s;
}

sf::Shape* RendererComponent::GetShape()
{
	return shape;
}

void RendererComponent::SetColor(int r, int g, int b)
{
	shape->setFillColor(sf::Color(r, g, b));
}

void RendererComponent::SetColor(sf::Color color)
{
	shape->setFillColor(color);
}

void RendererComponent::SetColor(sf::Vector3f color)
{
	shape->setFillColor(sf::Color(color.x, color.y, color.z));
}
