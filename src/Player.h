#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMovingX();
	void stopMovingY();

	bool isColliding(GameObject*);
	float getDistance(GameObject*);

private:

	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;
};

#endif /* defined (__PLAYER__) */