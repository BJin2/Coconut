#include "Engines/Game.h"

HWND Game::hWnd = 0;
Game::GameState Game::gameState = Game::GameState::Uninitialized;
Scene* Game::scene = nullptr;
//int CALLBACK WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow)
int main()
{
	Game::Initialize();
	Game::Start();

	return 0;
}