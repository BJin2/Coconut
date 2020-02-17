//
//  GraphicEngine.cpp
//  Engine
//
//  Created by heaseo chung on 2019-10-19.
//  Copyright © 2019 heaseo chung. All rights reserved.
//

#include "GraphicEngine.hpp"
#include "Scene.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/RendererComponent.h"

GraphicEngine* GraphicEngine::instance;

GraphicEngine::GraphicEngine()
{
	m_pGameScreen = new sf::RenderWindow(sf::VideoMode(640, 480), "Game Screen", sf::Style::Titlebar);
	m_pGameScreen->setActive(true);
}

GraphicEngine::~GraphicEngine()
{
	delete m_pGameScreen;
	delete instance;
}

GraphicEngine* GraphicEngine::Instance()
{
	if (instance)
		return instance;

	return instance = new GraphicEngine();
}

void GraphicEngine::Render()
{
	if (m_pGameScreen->isOpen())
	{
		m_pGameScreen->clear(sf::Color(255, 255, 255, 255));
		for (auto rItem : m_pRenderTarget)
		{
			sf::Transform state = rItem->GetOwner()->transform->GetTransform();
			m_pGameScreen->draw(*rItem->GetShape(), state);
		}
		m_pGameScreen->display();
	}
}

void GraphicEngine::RegisterRenderTarget(RendererComponent* rItem)
{
	m_pRenderTarget.push_back(rItem);
}

sf::RenderWindow* GraphicEngine::GetGameScreen()
{
	return m_pGameScreen;
}
