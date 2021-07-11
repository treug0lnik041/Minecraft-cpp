#pragma once
#include <SFML/Graphics.hpp>

#ifdef _DEBUG
#include "Engine/consolelogger.h"
#else
#include "Engine/winlogger.h"
#endif

#include "Engine/GLTK/Shader.h"

namespace Minecraft
{
	class Application
	{
	private:
		sf::RenderWindow* window;
		Engine::logger logger;

	private:
		void SFML_init(sf::VideoMode mode, std::string window_name);
		void OpenGL_init();

	private:
		static void _debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* classptr);
	public:
		Application();
		~Application();

	public:
		void run();
	};
}