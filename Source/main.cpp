#include "Engines/Game.h"
#include "../Source/Initializer.h"

Game* gGame;
HWND Game::hWnd = 0;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	Initializer* initializer = new Initializer();
	if (initializer->CheckRequirements("", 1000, 1000, 1000))
	{
		gGame = new Game();
		gGame->CreateEngineWindow(hInstance, 0, lpCmdLine, nCmdShow);
		gGame->Start();
		gGame->Update(0.0f);

		delete gGame;
	}

	return 0;
}