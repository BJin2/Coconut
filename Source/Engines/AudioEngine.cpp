//
//  AudioEngine.cpp
//  Engine
//
//  Created by heaseo chung on 2019-10-19.
//  Copyright © 2019 heaseo chung. All rights reserved.
//

#include "AudioEngine.hpp"
#include "Scene.h"

AudioEngine* AudioEngine::instance;

AudioEngine::AudioEngine()
{

}

AudioEngine::~AudioEngine()
{
	delete instance;
}

AudioEngine* AudioEngine::Instance()
{
	if (instance)
		return instance;

	return instance = new AudioEngine();
}

void AudioEngine::RegisterAudioTarget(AudioComponent* aItem)
{
	m_pAudioTarget.push_back(aItem);
}