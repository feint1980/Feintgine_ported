

#include "Window.h"
#include "Error.h"


namespace Feintgine{

	Window::Window()
	{
	}


	Window::~Window()
	{
	}
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlag)
	{



		if (glContext)
		{
			std::cout << "destroy old context \n";
			SDL_GL_DeleteContext(glContext);
		}
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		//SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		m_screenHeight = screenHeight;
		m_screenWidth = screenWidth;
		m_resolutionWidth = Width;
		m_resolutionHeight = Height;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
// 		if (windowFlag & FULLSCREEN)
// 		{
// 			std::cout << "calculate new solution \n";
// 			m_screenWidth = m_resolutionWidth;
// 			m_screenHeight = m_resolutionHeight;
// 		}
		
		m_aspectRatio =  (float)m_screenWidth /(float)m_resolutionWidth;
		std::cout << "new aspect is " << m_aspectRatio << "\n";

		Uint32 flags = SDL_WINDOW_OPENGL;
		flags |= SDL_WINDOW_ALLOW_HIGHDPI;
		if (windowFlag & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;

		}
		if (windowFlag & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (windowFlag & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), 0, 0, m_screenWidth, m_screenHeight, flags);
		int w;
		int h;
		//SDL_SetWindowSize(_sdlWindow, 1280, 720);
		SDL_GetWindowSize(_sdlWindow, &w, &h);
		std::cout << "created at " << w << " and " << h << "\n";
		
		
		
		if (_sdlWindow == nullptr)
		{
			fatalError("ko tao dc , chac thieu RAM !");
		}
	 
		glContext = SDL_GL_CreateContext(_sdlWindow);
		SDL_GL_MakeCurrent(_sdlWindow, glContext);
		if (glContext == nullptr)
		{
			fatalError("ko tao dc context OPENGL , chac card cui` ! ");
		}
		//GLenum error = glewInit();
		//if (error != GLEW_OK)
		//{
		//	fatalError("glew co van de ");
		//}
		std::cout << "context is " << glContext << "\n";

		glClearColor(0, 0, 0, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}
	void Window::swapBuffer()
	{

		SDL_GL_SwapWindow(_sdlWindow);
	}

	void Window::loadContext(SDL_GLContext context)
	{
		glContext = context;
		SDL_GL_MakeCurrent(_sdlWindow, glContext);
		std::cout << "context load is " << glContext << "\n";
	}

	void Window::deleteWindow()
	{
		
		SDL_DestroyWindow(_sdlWindow);
	}

	void Window::saveContext(SDL_GLContext context)
	{
		m_savedContext = context;
	}

	void Window::storageCamPos(glm::vec2 pos)
	{
		m_cameraStorePos = pos;
	}

}
