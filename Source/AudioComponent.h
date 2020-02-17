#pragma once
#include "ActorComponent.h"
#include <SFML/Graphics.hpp>

class AudioComponent : public ActorComponent
{
public:
	virtual void VStart() override;
	virtual void VUpdate(float dt) override;
private:
	sf::SoundBuffer buffer;
};