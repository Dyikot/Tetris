#define SDL_MAIN_HANDLED
#include "Application/Game.h"

#ifdef NDEBUG
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
{
	Game().Run();
}
#else
int main()
{
	Game().Run();
}
#endif