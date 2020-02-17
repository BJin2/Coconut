#include "AudioComponent.h"
#include "../../Engines//AudioEngine.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"


void AudioComponent::VStart()
{
	AudioEngine::Instance()->RegisterAudioTarget(this);
	if (buffer.loadFromFile("../../../Assets/Sounds/file_example_WAV_1MG.wav"))
	{
		sound.setBuffer(buffer);
		Loop(false);
		SetVolume(100.0f);
	}
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
	sound.setLoop(loop);
}

void AudioComponent::SetVolume(float volume)
{
	if (volume > 100.0f) volume = 100.0f;
	else if (volume < 0.0f) volume = 0.0f;
	sound.setVolume(volume);
}