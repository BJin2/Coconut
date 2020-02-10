#pragma once
#include "ActorComponent.h"

class IAbilities : public ActorComponent
{
public:
	virtual const char* VGetName() = 0;
	virtual void VAbilityAction() = 0;// to make this class an interface
};