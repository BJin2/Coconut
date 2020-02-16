#include "Engines/Game.h"

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