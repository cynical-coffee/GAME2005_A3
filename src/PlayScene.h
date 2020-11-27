#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "BulletPool.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	/*Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	bool m_playerFacingRight;*/

	const float bulletSpawnTimerDuration = 400.0f;
	float bulletSpawnTimerStart;

	Player* m_pPlayer;
	BulletPool* m_pPool;

	void SpawnBullet();

	// UI Items
	Button* m_pBackButton;
	
};

#endif /* defined (__PLAY_SCENE__) */