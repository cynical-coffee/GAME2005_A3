#include "Part2Scene.h"
#include "../src/Game.h"
#include "../src/EventManager.h"
#include "../src/Util.h"


// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "../src/Renderer.h"

const SDL_Color white = { 255, 255, 255, 255 };
const SDL_Color blue = { 0, 0, 255, 255 };

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

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void Part2Scene::update()
{
	updateDisplayList();
	/*
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
	*/
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
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Part2 Scene";

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

	// Instruction Label
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas", 12, white);
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);
	addChild(m_pInstructionsLabel);

	// Scale label
	m_pInstructionsLabel = new Label("Scale = 10 meters per pixel", "Consolas", 12, white);
	m_pInstructionsLabel->getTransform()->position = glm::vec2(400, 30.0f);
	addChild(m_pInstructionsLabel);

	// Distance Label
	m_pdistanceLabel = new Label("Distance", "Consolas", 12, white, glm::vec2(400.0f, 45.0f));
	m_pdistanceLabel->setParent(this);
	addChild(m_pdistanceLabel);

	// Velocity Label
	m_pVelocityLabel = new Label("Velocity", "Consolas", 12, white, glm::vec2(400.0f, 60.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);

	// Acceleration Label
	m_pAccLabel = new Label("Acceleration", "Consolas", 12, white, glm::vec2(400.0f, 75.0f));
	m_pAccLabel->setParent(this);
	addChild(m_pAccLabel);

	// NetForce
	m_pFNetLabel = new Label("Net Force", "Consolas", 12, white, glm::vec2(400.0f, 90.0f));
	m_pFNetLabel->setParent(this);
	addChild(m_pFNetLabel);
}

void Part2Scene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	

	ImGui::SetNextWindowPos(ImVec2(250, 165)); // hardcoded the position of imgui
	ImGui::Begin("Physics Control", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);



	ImGui::Separator();

	// gravity check
	static bool gravcheck = false;
	if (ImGui::Checkbox("Gravity", &gravcheck))
	{
		m_pBouncyBall->isGravityEnabled = gravcheck;
	}

	// Mass
	static float mass = 1.0f;
	ImGui::SliderFloat("Mass in kg", &mass, 1.0f, 100.0f);

	// Display distance
	std::string labelText = "";
	labelText = "Distance = " + std::to_string(m_pBouncyBall->getDistance(m_pBrick));
	m_pdistanceLabel->setText(labelText);

	// Display velocity
	float x = m_pBouncyBall->getRigidBody()->velocity.x;
	float y = m_pBouncyBall->getRigidBody()->velocity.y / 10;
	float magnitude = sqrt(x * x + y * y);
	m_pVelocityLabel->setText("Velocity = " + std::to_string((magnitude)));

	// Display Acceleration
	m_pAccLabel->setText("Acceleration = " + std::to_string(m_pBouncyBall->getRigidBody()->acceleration.y));

	// Display Net Force
	m_pFNetLabel->setText("Net Force = " + std::to_string(mass * m_pBouncyBall->getRigidBody()->acceleration.y));

	// WholeBrick
	if (CollisionManager::circleAABBCheck(m_pBouncyBall, m_pBrick))
	{
		m_pBouncyBall->getRigidBody()->velocity.y = -m_pBouncyBall->getRigidBody()->velocity.y * 1.25;
		m_pBouncyBall->getRigidBody()->acceleration.y -= m_pBouncyBall->getRigidBody()->acceleration.y;
		m_pAccLabel->setText("Acceleration = " + std::to_string(m_pBouncyBall->getRigidBody()->acceleration.y));
		m_pFNetLabel->setText("Net Force = " + std::to_string(mass * m_pBouncyBall->getRigidBody()->acceleration.y));
		m_pdistanceLabel->setText("HIT");
	}

	// LeftBrick
	if (CollisionManager::circleAABBsquaredDistance(m_pBouncyBall->getTransform()->position, m_pBouncyBall->getHeight() * 0.5,
		m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0.5, m_pBrick->getHeight()), m_pBrick->getWidth() * 0.5, m_pBrick->getHeight() * 0.5)
		< (m_pBouncyBall->getHeight() * 0.5 * m_pBouncyBall->getHeight() * 0.5))
	{
		m_pBouncyBall->getRigidBody()->velocity.x = -10;
		
		m_pBouncyBall->getRigidBody()->acceleration.y -= m_pBouncyBall->getRigidBody()->acceleration.y;
		m_pAccLabel->setText("Acceleration = " + std::to_string(m_pBouncyBall->getRigidBody()->acceleration.y));
		m_pFNetLabel->setText("Net Force = " + std::to_string(mass * m_pBouncyBall->getRigidBody()->acceleration.y));
	}
	// RightBrick
	else if (CollisionManager::circleAABBsquaredDistance(m_pBouncyBall->getTransform()->position, m_pBouncyBall->getHeight() * 0.5,
		m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0, m_pBrick->getHeight()),
		m_pBrick->getWidth() * 0.5, m_pBrick->getHeight() * 0.5)
		< (m_pBouncyBall->getHeight() * 0.5 * m_pBouncyBall->getHeight() * 0.5))
	{
		m_pBouncyBall->getRigidBody()->velocity.x = 10;
	
		m_pBouncyBall->getRigidBody()->acceleration.y -= m_pBouncyBall->getRigidBody()->acceleration.y;
		m_pAccLabel->setText("Acceleration = " + std::to_string(m_pBouncyBall->getRigidBody()->acceleration.y));
		m_pFNetLabel->setText("Net Force = " + std::to_string(mass * m_pBouncyBall->getRigidBody()->acceleration.y));
	}

	


	ImGui::End();
	// Don't Remove this
	ImGui::Render();

	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}