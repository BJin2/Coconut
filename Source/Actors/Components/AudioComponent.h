#pragma once
#include "ActorComponent.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AudioComponent : public ActorComponent
{
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

	void Play();
	void Stop();
	void Loop(bool loop);
	void SetVolume(float volume);
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};