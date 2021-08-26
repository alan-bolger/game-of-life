#include "Application.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

/// <summary>
/// Conway's Game of Life - an example of cellular automata.
/// </summary>
/// <returns>1 for successful exit.</returns>
int WINAPI wWinMain(_In_ HINSTANCE t_instance, _In_opt_ HINSTANCE, _In_ PWSTR t_cmdLine, _In_ int t_cmdShow)
{
	MessageBoxW(NULL, L"It's not actually a game, it's cellular automata.\n\nNo controls, just let it run and watch the creation of life.", L"Conway's Game of Life", MB_OK | MB_ICONASTERISK);

	Application &f_app = Application();
	f_app.run();

	return 1;
}