#include "Application.h"
#include <GL/glew.h>

void Minecraft::Application::SFML_init(sf::VideoMode mode, std::string window_name)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	this->window = new sf::RenderWindow(mode, window_name, sf::Style::Default, settings);
}

void Minecraft::Application::OpenGL_init()
{
	if (glewInit() != GLEW_OK)
		throw std::exception("unable to initialize GLEW");


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	glDebugMessageCallback(this->_debugfunc, &this->logger);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void Minecraft::Application::_debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* classptr)
{
	Engine::Logger* logger = (Engine::Logger*)classptr;

	Engine::Logger::severity sev;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		sev = Engine::Logger::severity::high;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		sev = Engine::Logger::severity::medium;
		break;
	case GL_DEBUG_SEVERITY_LOW:
		sev = Engine::Logger::severity::low;
		break;
	default:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		sev = Engine::Logger::severity::notification;
		break;
	}

	*logger << Engine::Logger::message("OpenGL debug info", message, sev);
}

Minecraft::Application::Application()
{
	this->SFML_init(sf::VideoMode(1000, 600), "Minecraft-cpp");
	this->OpenGL_init();
}

Minecraft::Application::~Application()
{
	delete this->window;
}

void Minecraft::Application::run()
{
	using Engine::gltk::Shader;

	Shader shader;

	try
	{
		shader.add(Shader::ShaderType::vertex, "shaders\\test\\vertex.glsl");
		shader.add(Shader::ShaderType::fragment, "shaders\\test\\fragment.glsl");
		shader.link();
	}
	catch (std::exception& e)
	{
		this->logger << Engine::Logger::message("OpenGL shader compiling error", e.what());
	}

	while (this->window->isOpen())
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			};
		}

		this->window->clear();
		this->window->display();

		//Print log information
		this->logger.flush();
	}
}