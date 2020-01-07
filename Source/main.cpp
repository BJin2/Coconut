#include "Engines/Game.h"

Game* gGame;
HWND Game::hWnd = 0;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	gGame = new Game();
	gGame->CreateEngineWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	gGame->Start();
	gGame->Update(0.0f);

	delete gGame;

	return 0;
}