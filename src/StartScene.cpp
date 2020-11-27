#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(PART2_SCENE);
	}
}

void StartScene::start()
{
	
	// Color Constants
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };

	m_pStartLabel = new Label("START SCENE", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play Scene 1", "Consolas", 15, blue, glm::vec2(400.0f, 520.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_pScene2Label = new Label("Press 2 to Play Scene 2", "Consolas", 15, blue, glm::vec2(400.0f, 550.0f));
	m_pScene2Label->setParent(this);
	addChild(m_pScene2Label);


	m_pStudentName = new Label("Jen Marc Capistrano", "Consolas", 30, red, glm::vec2(400.0f, 120.0f));
	m_pStudentName->setParent(this);
	addChild(m_pStudentName);

	m_pStudentName = new Label("101218004", "Consolas", 20, red, glm::vec2(400.0f, 160.0f));
	m_pStudentName->setParent(this);
	addChild(m_pStudentName);

	m_pStudentName = new Label("Meghan Paris", "Consolas", 30, red, glm::vec2(400.0f, 200.0f));
	m_pStudentName->setParent(this);
	addChild(m_pStudentName);

	m_pStudentName = new Label("101232052", "Consolas", 20, red, glm::vec2(400.0f, 240.0f));
	m_pStudentName->setParent(this);
	addChild(m_pStudentName);


	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	addChild(m_pShip);


	m_pStartButton = new Button("../Assets/textures/scene1Button.png", "scene1", SCENE_1_BUTTON);
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);

	m_pStartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pStartButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStartButton->setAlpha(128);
		});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStartButton->setAlpha(255);
		});
	addChild(m_pStartButton);
	

	// scene 2 button
	m_pScene2 = new Button("../Assets/textures/scene2Button.png", "scene2", SCENE_2_BUTTON);
	m_pScene2->getTransform()->position = glm::vec2(400.0f, 475.0f);

	m_pScene2->addEventListener(CLICK, [&]()-> void
	{
			m_pScene2->setActive(false);
		TheGame::Instance()->changeSceneState(PART2_SCENE);
	});
	
	m_pScene2->addEventListener(MOUSE_OVER, [&]()->void
	{
			m_pScene2->setAlpha(128);
	});

	m_pScene2->addEventListener(MOUSE_OUT, [&]()->void
	{
			m_pScene2->setAlpha(255);
	});
	addChild(m_pScene2);

	
}

