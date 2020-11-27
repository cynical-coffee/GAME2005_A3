#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	SDL_GetTicks();
	float deltaTime = 1.0f / 60.0f;
	updateDisplayList();

	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration)
	{
		SpawnBullet();
	}

	std::vector<Bullet*>& activeBullets = m_pPool->all;
	for (auto myIter = activeBullets.begin(); myIter != activeBullets.end(); ++myIter)
	{
		Bullet* bullet = *myIter;
		if (bullet->active && bullet->getTransform()->position.y >= 650)
		{
			m_pPool->Despawn(bullet);
			break;
		}
	}

	m_pPool->IsColliding(m_pPlayer);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else {
		m_pPlayer->stopMovingX();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMovingY();
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{

	// Background
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pPlayer = new Player();
	addChild(m_pPlayer);

	m_pPool = new BulletPool(10);

	for (auto myIter = m_pPool->all.begin(); myIter != m_pPool->all.end(); ++myIter)
	{
		Bullet* bullet = *myIter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();

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

void PlayScene::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0.0);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Simple 2D Collision", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	

	/*if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}*/
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
