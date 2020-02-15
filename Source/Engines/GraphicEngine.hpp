#pragma once
#include <SFML/Graphics.hpp>

class Scene;
class RendererComponent;

class GraphicEngine
{
private:
	GraphicEngine();
	~GraphicEngine();
	static GraphicEngine* instance;
	sf::RenderWindow* m_pGameScreen;
	std::vector<RendererComponent*> m_pRenderTarget;

public:
	static GraphicEngine* Instance();
	void Render();
	void RegisterRenderTarget(RendererComponent* rItem);
};
