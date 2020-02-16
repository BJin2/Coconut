#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"

void RendererComponent::VStart()
{
	GraphicEngine::Instance()->RegisterRenderTarget(this);
	size = sf::Vector2f(100, 100);
	SetShape(new sf::RectangleShape(sf::Vector2f(size.x, size.y)));
	shape->setOrigin(size.x/2, size.y/2);
	shape->setPosition(shape->getOrigin().x, shape->getOrigin().y);
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
	if (!texture.loadFromFile(textureFile))
	{
		sf::Uint8* pixels = new sf::Uint8[size.x * size.y * 4];
		texture.update(pixels);
	}
}

void RendererComponent::SetSize(sf::Vector2f _size)
{
	size = _size;
}