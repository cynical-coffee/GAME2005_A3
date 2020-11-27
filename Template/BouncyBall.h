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

	
	bool isGravityEnabled = false;
	float getDistance(GameObject*);
	bool isColliding(GameObject*);

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
	
	const int FPS = 60;
	float deltaTime = 1.0f / FPS;
	float elasticity = 0.6f;
	const float mpp = 10.0f; // 5 meter per pixel
	const glm::vec2 gravity = glm::vec2(0.0f, 9.8f);
	
};

#endif /* defined (__BOUNCY_BALL__) */