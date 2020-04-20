#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "Initializer.h"
#include "InputInterface.h"	
#include "GraphicEngine.hpp"
#include "PhysicsEngine.hpp"
#include "AudioEngine.hpp"
#include "ScriptManager.hpp"
#include "../CoconutEngine/CoconutEngine/resource.h"
#include "../Engines/XMLCompiler.h"

//Event example
#include "Event/EventManager.h"
#include "Event/EventMapper.h"
#include "Event/ExampleLoadedEvent.h"

HWND Game::hWnd = 0;
Game::GameState Game::gameState = Game::GameState::Uninitialized;
Scene* Game::scene;
Time* Game::time;
EventMapper* Game::mapper;
XMLCompiler* Game::xml;

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Coconut Engine");

auto timePerFrame = (1 / 60.0f);

void Game::Clear()
{
	printf("Deleting");
	delete scene;
	delete mapper;
	delete time;
	delete PhysicsEngine::Instance();
	delete GraphicEngine::Instance();
	delete AudioEngine::Instance();
	delete EventManager::Instance();
	delete ScriptManager::Instance();
}

void Game::Start()
{
	if (gameState == GameState::Uninitialized)
		return;

	CreateEngineWindow(nullptr, szTitle, SW_SHOW);
	gameState = GameState::Playing;
	time->Start();
	scene->Start();
	ScriptManager::Instance()->Start();
	Update();
}

void Game::Initialize()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(370, 270), "Splash Screen", sf::Style::None);
	window->setActive(true);

	if (window->isOpen())
	{
		sf::Texture splashScreenTexture;
		sf::Sprite splashScreenSprite;

		window->clear();
		//splashScreenTexture.loadFromFile("..\..\Assets\Textures\CoconutEngineLogo.PNG")
		if (splashScreenTexture.loadFromFile("../../../Assets/Textures/CoconutEngineLogo.png"))
		{
			splashScreenSprite.setTexture(splashScreenTexture);
			splashScreenSprite.setTextureRect(sf::IntRect(0, 0, 370, 270));
		}

		if (splashScreenSprite.getTexture() != NULL)
		{
			window->draw(splashScreenSprite);
		}
		else
		{		
			window->clear(sf::Color(255, 0, 0, 255));
		}
		window->display();
	}

	Initializer* initializer = new Initializer();
	if (initializer->CheckRequirements(szTitle, 800, 800, 800))
	{
		gameState = GameState::ShowingSplash;
	}
	delete initializer;

	//Event System Example
	mapper = new EventMapper();
	EventManager::Instance()->RegisterMapper(GraphicEngine::Instance()->GetGameScreen(), mapper);
	mapper->SetOnEvent([](const IEvent* e)->void
		{
			ExampleLoadedEventData* exampleData = static_cast<ExampleLoadedEventData*>(e->GetData());
			std::cout << exampleData->example << std::endl;
		}, ExampleLoadedEventData::type);

	time = new Time();
	scene = new Scene();
	scene->Initialize();
	ScriptManager::Instance()->SetScene(scene);
	ScriptManager::Instance()->Initialize();
	delete window;
}

void Game::Update()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		time->Update();
		scene->Update(time->GetDeltaTime());

		time->SetTimeSinceLastUpdate(time->GetDeltaTime());
		while (time->GetTimeSinceLastUpdate() > timePerFrame)
		{
			time->SetTimeSinceLastUpdate(-timePerFrame);

			//Fixed Update
			PhysicsEngine::Instance()->UpdatePhysics(timePerFrame);
			ScriptManager::Instance()->Update(timePerFrame);
		}
		GraphicEngine::Instance()->Render();
	}
	Clear();
}

bool Game::CreateEngineWindow(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}


	HWND hWnd = CreateWindow(
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 512,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}
	Game::hWnd = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	IInput input;

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_SAVE:
			printf("SAVED");
			xml->XMLSave("../../../Assets/Scene1.xml",scene);
			break;
		case ID_FILE_LOAD:
			//xml->XMLLoad(,scene);
			break;
		}
		break;
	case WM_CHAR:
		input.VOnChar(wParam, hWnd);
		break;
	case WM_KEYDOWN:
		input.VOnKeyDown(wParam, hWnd);
		break;
	case WM_KEYUP:
		input.VOnKeyUp(wParam, hWnd);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		input.VOnPointerMove(lParam, hWnd);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		input.VOnPointerButtonDown(lParam, hWnd);
		break;
	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		input.VOnPointerButtonUp(lParam, hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
