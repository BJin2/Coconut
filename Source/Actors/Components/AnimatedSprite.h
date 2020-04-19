#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "ActorComponent.h"
#include "Animation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable, public ActorComponent
{
public:
	explicit AnimatedSprite(float frameTime = 0.2f, bool paused = false, bool looped = true);

	virtual void VStart() override;
	virtual void VUpdate(float dt) override;
	
	void setAnimation(const Animation& animation);
	void setFrameTime(float time);
	void play();
	void play(const Animation& animation);
	void pause();
	void stop();
	void setLooped(bool looped);
	void setColor(const sf::Color& color);
	const Animation* getAnimation() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isLooped() const;
	bool isPlaying() const;
	float getFrameTime() const;
	void setFrame(std::size_t newFrame, bool resetTime = true);

private:
	const Animation* m_animation;
	float m_frameTime;
	float m_currentTime;
	std::size_t m_currentFrame;
	bool m_isPaused;
	bool m_isLooped;
	const sf::Texture* m_texture;
	sf::Vertex m_vertices[4];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
};