#ifndef __APP_H__
#define __APP_H__

#include <IMainGame.h>

#include "MainMenuScreen.h"

class App : public Feintgine::IMainGame
{
public :
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreen() override;
	virtual void onExit() override;
private:
	std::unique_ptr<MainMenuScreen>m_mainMenuScreen = nullptr;

};


#endif


