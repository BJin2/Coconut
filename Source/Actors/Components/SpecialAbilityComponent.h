#pragma once
#include "AbilitiesInterface.h"

class SpecialAbilityComponent : public IAbilities
{
public:
	//bool VInit(TiXmlElement* pData) override;
	const char* VGetName() override;
	void VAbilityAction() override;
};