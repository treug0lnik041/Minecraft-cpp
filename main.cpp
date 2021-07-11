#include "Application.h"

#ifdef _DEBUG
int main()
{
	Minecraft::Application app;
	app.run();
}
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR nCmdLine, int nCmdShow)
{
	Minecraft::Application app;
	app.run();
}
#endif