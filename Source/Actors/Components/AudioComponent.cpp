#include "AudioComponent.h"
#include "../../Engines//AudioEngine.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"


AudioComponent::AudioComponent()
{
	AudioEngine::Instance()->RegisterAudioTarget(this);
	loop = false;
	volume = 100.0f;
}

AudioComponent::~AudioComponent()
{
	AudioEngine::Instance()->DestroyAudioTarget(this);
}

void AudioComponent::VStart()
{
	
}

void AudioComponent::VUpdate(float dt)
{

}

void AudioComponent::Play()
{
	sound.play();
}

void AudioComponent::Stop()
{
	sound.stop();
}

void AudioComponent::Loop(bool loop)
{
	this->loop = loop;
	sound.setLoop(loop);
}

void AudioComponent::SetVolume(float volume)
{
	this->volume = volume;
	if (volume > 100.0f) volume = 100.0f;
	else if (volume < 0.0f) volume = 0.0f;
	sound.setVolume(volume);
}

void AudioComponent::SetSound(std::string path)
{
	AudioEngine::Instance()->RegisterAudioTarget(this);
	if (buffer.loadFromFile(path))
	{
		sound.setBuffer(buffer);
		Loop(loop);
		SetVolume(volume);
	}
}
