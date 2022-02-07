#ifndef __MAIN_MENU_SCREEN_H__
#define __MAIN_MENU_SCREEN_H__


#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector> 
#include <Window.h>
#include <SpriteBatch.h>
#include <IGameScreen.h>
#include <gl31.h>
#include <EmptyObject.h>
#include <ResourceManager.h>
#include <IMainGame.h>

class MainMenuScreen : public Feintgine::IGameScreen
{
public : 
	MainMenuScreen();
	~MainMenuScreen();

	MainMenuScreen(Feintgine::Window * window);
	


	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	void handleInput(Feintgine::InputManager & inputManager);

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	void initShader();

	virtual void checkInput() override;

private:
	Feintgine::Camera2D m_camera;
	Feintgine::SpriteBatch m_spriteBatch;
	Feintgine::GLSLProgram m_shader;
	EmptyObject testObj;

};

#endif
