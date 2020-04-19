#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:

	const sf::Texture* m_texture;

public:
	std::vector<sf::Texture> m_frames;
	Animation();
	~Animation();

	void AddFrame(sf::Texture frame);
	void SetSpriteSheet(const sf::Texture texture);
	const sf::Texture* GetSpriteSheet() const;
	std::size_t GetSize() const;
	const sf::Texture GetFrame(std::size_t n) const;
};