#include "Engines/Game.h"
#include "Engines/Utils.h"

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
	Vector2 a = Vector2(2, 2);
	Matrix translate = Matrix::Identity;
	translate = translate.scale(a);
	auto temp = translate.getMatrix();
	printf("%f", a.x);
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
			printf("\n");
		printf("%f, ", temp[i]);
	}
	printf("\n");
	Game::Initialize();
	Game::Start();

	return 0;
}