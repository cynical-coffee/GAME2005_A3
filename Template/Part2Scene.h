#pragma once
#ifndef __PART2_SCENE__
#define __PART2_SCENE__

#include "../src/Scene.h"
#include "BouncyBall.h"
#include "Brick.h"
#include "../src/Button.h"
#include "../src/Label.h"


class Part2Scene : public Scene
{
public:
	Part2Scene();
	~Part2Scene();

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


	// Bouncy Ball
	BouncyBall* m_pBouncyBall;
	
	
	// Brick
	Brick* m_pBrick;

	// Back Button
	Button* m_pBackButton;

	// UI Items
	Label* m_pInstructionsLabel;
	Label* m_pdistanceLabel;
	Label* m_pVelocityLabel;
	Label* m_pAccLabel;
	Label* m_pAngleLabel;
	Label* m_pFFrictionLabel;
	Label* m_pFNormalLabel;
	Label* m_pFGravityLabel;
	Label* m_pFNetLabel;
};

#endif /* defined (__PART2_SCENE__) */