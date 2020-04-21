#pragma once
#include "ActorComponent.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AudioComponent : public ActorComponent
{
public:
	AudioComponent();
	~AudioComponent();
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;

	void Play();
	void Stop();
	void Loop(bool loop);
	void SetVolume(float volume);
	void SetSound(std::string p);
	void SetSound();
	void SetPath(std::string p);
	void SetIsPlaying(bool p);
	bool GetIsPlaying();
	std::string GetPath();
	bool GetLoop();
	float GetVolume();

private:
	float volume;
	bool loop;
	bool isPlaying;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string path;
};