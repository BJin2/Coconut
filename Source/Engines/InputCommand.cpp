//
//  InputCommand.cpp
//  Engine
//
//  Created by heaseo chung on 2019-10-19.
//  Copyright © 2019 heaseo chung. All rights reserved.
//

#include "InputCommand.hpp"
#include "GraphicEngine.hpp"

bool InputCommand::GetKeyDown(Key key)
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
}

bool InputCommand::GetMouseLeft()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool InputCommand::GetMouseRight()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}