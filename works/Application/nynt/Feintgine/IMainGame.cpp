#include "IMainGame.h"
#include "Timing.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "EngineSetting.h"
#include "F_oEvent.h"

namespace Feintgine
{
	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique<ScreenList>(this);
	}


	IMainGame::~IMainGame()
	{
	}

	void IMainGame::run()
	{

		if (!init())
		{
			return;
		}
		FpsLimiter limiter;
		limiter.setMaxFPS(ENGINE_targetFPS);
		float prevTicks = SDL_GetTicks();
		m_isRunning = true;

		

	   // float MAX_STEPS 
// 		if (!m_isLoaded)
// 		{
// 
// 			drawLoadingScreen();
// 		}
		const float MS_PER_SECOND = 1000;
		while (m_isRunning)
		{
			
			const float TARGET_FRAMETIME = MS_PER_SECOND / ENGINE_targetFPS;

			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - prevTicks;
			prevTicks = newTicks;
			float totalDeltaTime =  frameTime / TARGET_FRAMETIME;
	
			while (totalDeltaTime > 0.0f)
			{
			
				float deltaTime = std::min(totalDeltaTime, 1.0f);
				//std::cout << "delta time " << deltaTime << "\n";

				
				update(deltaTime);
				totalDeltaTime -= deltaTime;
				
			}
			checkInput();
			//std::cout << fps << "\n";
			m_inputManager.update();
			draw();
			fps = limiter.end();
			m_window.swapBuffer();
									
		}
	}
	void IMainGame::exitGame()
	{
		m_screenList->onExit();

		if (m_screenList)
		{
			m_screenList->destroy();
			m_screenList.reset();
		}
		m_isRunning = false;

	}

	bool IMainGame::init()
	{
		Feintgine::initFeint();
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		if (!initSystem())
		{
			return false;
		}
		
		onInit();

		addScreen();

		
		m_currentScreen = m_screenList->getCurrentGameScreen();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();
		
		
		return true;

	}
	bool IMainGame::initSystem()
	{
		// 1366 x 768
		// 1920 x 1080

		m_window.create("Gensokyo Adventure", 800, 480, 0);
		return true;
	}

	void IMainGame::update(float deltaTime)
	{
		if (m_currentScreen)
		{
			switch (m_currentScreen->getState())
			{ 
			case ScreenState::RUNNING :
				if (ENGINE_isGameRunning)
				{
					
					
					
					m_currentScreen->update(deltaTime);
				}
				//std::cout << ENGINE_current_tick << " tick \n";
				
				
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen)
				{
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;

			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen)
				{
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;


			default:
				break;
			}
		}
		else
		{
			exitGame();
		}
	}
	void IMainGame::draw()
	{
		//int dif_x = m_window.getResolutionWidth() - m_window.getScreenWidth();
		//int dif_y = m_window.getResolutionHeight() - m_window.getScreenHeight();
		
		//glViewport(-dif_x/2 , -dif_y/2, m_window.getScreenWidth() / m_window.getAspect() , m_window.getScreenHeight() / m_window.getAspect());
		//glViewport(vp_x, vp_y, convertedWidth, convertedHeight);
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING)
		{
			m_currentScreen->draw();
		}
	}

	void IMainGame::checkInput()
	{
		m_currentScreen->checkInput();
	}

	void IMainGame::onSDLEvent(SDL_Event & evnt)
	{
		switch (evnt.type) {
		
		
		case SDL_WINDOWEVENT_CLOSE:
			exitGame();
			break;
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
		if (evnt.key.keysym.scancode)
		{
			anykey = true;
		}
		else
		{
			anykey = false;
		}
	
		
	}


	void IMainGame::updateTimer(float deltaTime)
	{

	}

	void IMainGame::configureScreen(std::string name, int screenWidth, int screenHeight, int t_flag, bool saveContext)
	{
		SDL_GLContext context = m_window.getGLContext();
	
		
		m_window.deleteWindow();	
		m_window.create(name, screenWidth, screenHeight, t_flag);
		if (saveContext)
		{
			m_window.loadContext(context);
		}
		
		
	}

}

