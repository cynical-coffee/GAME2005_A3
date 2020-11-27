#pragma once
#ifndef __BOUNCY_BALL__
#define __BOUNCY_BALL__

#include "../src/DisplayObject.h"
#include "../src/CollisionManager.h"
#include "Brick.h"

class BouncyBall final : public DisplayObject {
public:
	BouncyBall();
	~BouncyBall();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	
	
private:
	void m_move();
	void m_checkBounds();
	void m_reset();
	
	const int FPS = 60;
	float deltaTime = 1.0f / FPS;
	float elasticity = 0.6f;

	
};

#endif /* defined (__BOUNCY_BALL__) */