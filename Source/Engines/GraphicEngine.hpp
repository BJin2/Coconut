#pragma once
#include <SFML/Graphics.hpp>

class Scene;
class RendererComponent;

class GraphicEngine
{
private:
	GraphicEngine();
	static GraphicEngine* instance;
	sf::RenderWindow* m_pGameScreen;
	std::vector<RendererComponent*> m_pRenderTarget;

public:
	~GraphicEngine();
	static GraphicEngine* Instance();
	void Render();
	void RegisterRenderTarget(RendererComponent* rItem);
	sf::RenderWindow* GetGameScreen();
};
