#pragma once
#include <iostream>
#include <atltypes.h>

class IInput {
public:
	virtual bool VOnKeyDown(unsigned int const kcode) = 0;
	virtual bool VOnKeyUp(unsigned int const kcode) = 0;

	virtual bool VOnPointerMove(const CPoint& mousePos) = 0;
	virtual bool VOnPointerButtonDown(const CPoint& mousePos, const std::string& buttonName) = 0;
	virtual bool VOnPointerButtonUp(const CPoint& mousePos, const std::string& buttonName) = 0;
	virtual int VGetPointerRadius() = 0;

};