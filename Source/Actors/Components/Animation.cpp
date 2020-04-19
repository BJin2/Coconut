#include "Animation.h"

Animation::Animation() : m_texture(NULL)
{
}

Animation::~Animation()
{
}

void Animation::AddFrame(sf::Texture frame)
{
	m_frames.push_back(frame);
}

void Animation::SetSpriteSheet(const sf::Texture texture)
{
	m_texture = &texture;
}

const sf::Texture* Animation::GetSpriteSheet() const
{
	return m_texture;
}

std::size_t Animation::GetSize() const
{
	return m_frames.size();
}

const sf::Texture Animation::GetFrame(std::size_t n) const
{
	return m_frames[n];
}
