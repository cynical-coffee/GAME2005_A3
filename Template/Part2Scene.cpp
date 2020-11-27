#include "Part2Scene.h"
#include "../src/Game.h"
#include "../src/EventManager.h"
#include "../src/Util.h"


Part2Scene::Part2Scene()
{
	Part2Scene::start();
}

Part2Scene::~Part2Scene()
= default;

void Part2Scene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	drawDisplayList();
}

void Part2Scene::update()
{
	updateDisplayList();

	// WholeBrick
	if (CollisionManager::circleAABBCheck(m_pBouncyBall, m_pBrick))
	{
		m_pBouncyBall->getRigidBody()->velocity.y = -m_pBouncyBall->getRigidBody()->velocity.y * 1.25;
	}


	// LeftBrick
	if (CollisionManager::circleAABBsquaredDistance(m_pBouncyBall->getTransform()->position, m_pBouncyBall->getHeight() * 0.5,
		m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0.5, m_pBrick->getHeight()), m_pBrick->getWidth() * 0.5, m_pBrick->getHeight() * 0.5)
		< (m_pBouncyBall->getHeight() * 0.5 * m_pBouncyBall->getHeight() * 0.5))
	{
		m_pBouncyBall->getRigidBody()->velocity.x = -100;

	}
	// RightBrick
	else if (CollisionManager::circleAABBsquaredDistance(m_pBouncyBall->getTransform()->position, m_pBouncyBall->getHeight() * 0.5,
		m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0, m_pBrick->getHeight()),
		m_pBrick->getWidth() * 0.5, m_pBrick->getHeight() * 0.5)
		< (m_pBouncyBall->getHeight() * 0.5 * m_pBouncyBall->getHeight() * 0.5))
	{
		m_pBouncyBall->getRigidBody()->velocity.x = 100;

	}

}

void Part2Scene::clean()
{
	removeAllChildren();
}

void Part2Scene::handleEvents()
{
	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().getMouseButton(CLICK))
	{
		m_pBrick->getTransform()->position = EventManager::Instance().getMousePosition();
		
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
	{
		clean();
		start();
	}
	
}

void Part2Scene::start()
{
	// Background
	TextureManager::Instance()->load("../Assets/textures/loaded.png", "background");

	

	// Brick Sprite
	m_pBrick = new Brick();
	addChild(m_pBrick);

	// Ball Sprite
	m_pBouncyBall = new BouncyBall();
	addChild(m_pBouncyBall);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(400.0f, 550.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
		{
			m_pBackButton->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pBackButton->setAlpha(128);
		});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pBackButton->setAlpha(255);
		});
	addChild(m_pBackButton);
}

