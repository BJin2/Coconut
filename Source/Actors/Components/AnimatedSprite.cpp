#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(float frameTime, bool paused, bool looped) :
	m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped), m_texture(NULL)
{

}

void AnimatedSprite::VStart()
{
}

void AnimatedSprite::VUpdate(float dt)
{
	if (!m_isPaused && m_animation)
	{
		// add delta time
		m_currentTime += dt;

		// if current time is bigger then the frame time advance one frame
		if (m_currentTime >= m_frameTime)
		{
			// reset time, but keep the remainder
			//m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
			m_currentTime = 0.0f;

			// get next Frame index
			if (m_currentFrame + 1 < m_animation->GetSize())
				m_currentFrame++;
			else
			{
				// animation has ended
				if (!m_isLooped)
				{
					m_isPaused = true;
				}
				else
				{
					m_currentFrame = 0; // reset to start
				}
			}

			// set the current frame, not reseting the time
			setFrame(m_currentFrame, false);
		}
	}
}

void AnimatedSprite::setAnimation(const Animation& animation)
{
	m_animation = &animation;
	m_texture = m_animation->GetSpriteSheet();
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void AnimatedSprite::setFrameTime(float time)
{
	m_frameTime = time;
}

void AnimatedSprite::play()
{
	m_isPaused = false;
}

void AnimatedSprite::play(const Animation& animation)
{
	if (getAnimation() != &animation)
		setAnimation(animation);
	play();
}
void AnimatedSprite::pause()
{
	m_isPaused = true;
}

void AnimatedSprite::stop()
{
	m_isPaused = true;
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void AnimatedSprite::setLooped(bool looped)
{
	m_isLooped = looped;
}

const Animation* AnimatedSprite::getAnimation() const
{
	return m_animation;
}

bool AnimatedSprite::isLooped() const
{
	return m_isLooped;
}

bool AnimatedSprite::isPlaying() const
{
	return !m_isPaused;
}
float AnimatedSprite::getFrameTime() const
{
	return m_frameTime;
}

void AnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
{
	if (m_animation)
	{
		m_animation->m_frames[newFrame];

		if (resetTime)
			m_currentTime = 0.0f;
	}
}

//void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	if (m_animation && m_texture)
//	{
//		states.transform *= getTransform();
//		states.texture = m_texture;
//		target.draw(m_vertices, 4, sf::Quads, states);
//	}
//}