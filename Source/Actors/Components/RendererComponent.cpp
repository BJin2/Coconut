#include "RendererComponent.h"
#include "../../Engines/GraphicEngine.hpp"
#include "../../Engines/InputCommand.hpp"

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
	if (InputCommand::GetKeyDown(InputCommand::Key::D))
	{
		Translate(sf::Vector2f(1, 0), 3 * dt);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::A))
	{
		Translate(sf::Vector2f(-1, 0), 3 * dt);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::W))
	{
		Translate(sf::Vector2f(0, 1), 3 * dt);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::S))
	{
		Translate(sf::Vector2f(0, -1), 3 * dt);
	}
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
}

void RendererComponent::Translate(sf::Vector2f dir, float speed)
{
	sf::Vector2f pos = shape->getPosition();
	shape->setPosition(pos.x + (dir.x * speed), pos.y - (dir.y * speed));
}