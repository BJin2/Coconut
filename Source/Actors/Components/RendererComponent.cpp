#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"

RendererComponent::RendererComponent()
{
	GraphicEngine::Instance()->RegisterRenderTarget(this);
	size = sf::Vector2f(100, 100);
	SetShape(new sf::RectangleShape(sf::Vector2f(size.x, size.y)));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	//shape->setPosition(shape->getOrigin().x, shape->getOrigin().y);
}

RendererComponent::~RendererComponent()
{
	delete shape;
	delete texture;
}

void RendererComponent::VStart()
{
	
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
	texture = new sf::Texture();
	if (texture->loadFromFile(textureFile))
	{
		texture->setSmooth(true);
		shape->setTexture(texture);
		sf::Vector2f temp = size;
		size = sf::Vector2f(texture->getSize().x, texture->getSize().y);
		printf("texture x %d", texture->getSize().x);
		shape->setOrigin(size.x / 2, size.y / 2);
		shape->setTextureRect(sf::IntRect(shape->getPosition().x, shape->getPosition().y, size.x, size.y));
		size = temp;
	}
}

void RendererComponent::SetSize(sf::Vector2f _size)
{
	size = _size;
	shape->setOrigin(size.x / 2, size.y / 2);
	dynamic_cast<sf::RectangleShape*>(shape)->setSize(size);
}