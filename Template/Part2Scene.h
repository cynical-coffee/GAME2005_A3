#pragma once
#ifndef __PART2_SCENE__
#define __PART2_SCENE__

#include "../src/Scene.h"
#include "BouncyBall.h"
#include "Brick.h"
#include "../src/Button.h"


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
	glm::vec2 m_mousePosition;


	// Bouncy Ball
	BouncyBall* m_pBouncyBall;
	
	
	// Brick
	Brick* m_pBrick;

	Button* m_pBackButton;
};

#endif /* defined (__PART2_SCENE__) */