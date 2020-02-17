#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"

void RendererComponent::VStart()
{
	GraphicEngine::Instance()->RegisterRenderTarget(this);
	size = sf::Vector2f(100, 100);
	SetShape(new sf::RectangleShape(sf::Vector2f(size.x, size.y)));
	shape->setOrigin(size.x/2.0f, size.y/2.0f);
	//shape->setPosition(shape->getOrigin().x, shape->getOrigin().y);
	SetColor(sf::Color::Black);
}

void RendererComponent::VUpdate(float dt)
{
}

void RendererComponent::SetShape(sf::Shape* s)
{
	shape = s;
}

void RendererComponent::SetColor(int r, int g, int b)
{
	shape->setFillColor(sf::Color(r, g, b));
}

void RendererComponent::SetColor(sf::Color color)
{
	shape->setFillColor(color);
}

void RendererComponent::SetTexture(std::string textureFile)
{
	if (texture->loadFromFile(textureFile))
	{
		shape->setTexture(texture);
		shape->setTextureRect(sf::IntRect(shape->getPosition().x, shape->getPosition().y, size.x, size.y));
	}
}

void RendererComponent::SetSize(sf::Vector2f _size)
{
	size = _size;
	shape->setOrigin(size.x / 2, size.y / 2);
}