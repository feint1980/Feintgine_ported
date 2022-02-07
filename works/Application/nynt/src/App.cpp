#include "App.h"


App::App()
{

}


App::~App()
{

		std::cout << "exit \n";
}


void App::onInit()
{
		
		
		
}



void App::addScreen()
{
	m_mainMenuScreen = std::make_unique<MainMenuScreen>(&m_window);
	m_screenList->addScreen(m_mainMenuScreen.get());
	m_screenList->setScreen(m_mainMenuScreen->getScreenIndex());

}

void App::onExit()
{

}
