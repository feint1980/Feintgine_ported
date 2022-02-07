#include "MainMenuScreen.h"
#include <iostream>
MainMenuScreen::MainMenuScreen()
{
}

MainMenuScreen::MainMenuScreen(Feintgine::Window * window)
{
		initShader();

		m_screenIndex = 15;
				
}

MainMenuScreen::~MainMenuScreen()
{
}

int MainMenuScreen::getNextScreenIndex() const
{
		return -1;
}

int MainMenuScreen::getPreviousScreenIndex() const
{
		return 1;
}

void MainMenuScreen::build()
{

}

void MainMenuScreen::destroy()
{

}

void MainMenuScreen::onEntry()
{

	m_spriteBatch.init();
	m_camera.init(800, 400);
	m_camera.setScale(1.0f);
	//m_camera.savePos();
	m_camera.setAngle(0.0f);
	testObj.init(Feintgine::ResourceManager::getTexture("Textures/test.png"), 
					glm::vec2(0,0), glm::vec2(800.0f, 480.0f), Feintgine::Color(255, 255,255, 255));
	
	
	//m_camera.setPosition(testObj.getPos());

	m_camera.update();
}


void MainMenuScreen::onExit()
{
	//m_audioEngine.destroy();
}

void MainMenuScreen::draw()
{
	//std::cout << "drawing \n";
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_shader.use();				

	GLint textureUniform = m_shader.getUniformLocation("mySampler");

	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();

	GLint pUniform = m_shader.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	m_spriteBatch.begin();

	testObj.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
//	m_shader.unuse();
	//SDL_GL_SetSwapInterval(1);
	//m_window->swapBuffer();

}

void MainMenuScreen::update(float deltaTime)
{
//	m_camera.setPosition(testObj.getPos());
//	m_camera.update();	
}


void MainMenuScreen::handleInput(Feintgine::InputManager & inputManager)
{


}


void MainMenuScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) 
	{
		m_game->onSDLEvent(evnt);
	}
//	handleInput(m_game->getInputManager());
}

void MainMenuScreen::initShader()
{
	m_shader.compileShaders("Shaders/normal.vert", "Shaders/normal.frag");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();

}

