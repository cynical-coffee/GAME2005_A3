#include "BouncyBall.h"
#include "../src/TextureManager.h"

#define WALL 800
#define CEILING 600

BouncyBall::BouncyBall()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 10.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(BOUNCYBALL);
}

BouncyBall::~BouncyBall()
= default;

void BouncyBall::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the BouncyBall
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void BouncyBall::update()
{
	m_move();
	m_checkBounds();
	
}

void BouncyBall::clean()
{
}

void BouncyBall::m_move()
{
		
	if (!isGravityEnabled)
	{
		getRigidBody()->acceleration = glm::vec2(0, 0);
	}
	else
	{
		// gravity
		getRigidBody()->velocity.y += gravity.y * deltaTime *mpp;
		getRigidBody()->acceleration = gravity;
		
	}

		
		getTransform()->position.y += getRigidBody()->velocity.y * deltaTime;
		getTransform()->position.x += getRigidBody()->velocity.x * deltaTime;
		
		
		
	
}

void BouncyBall::m_checkBounds()
{
	// floor
	if (getTransform()->position.y + getHeight() / 2 >= CEILING)
	{
		getRigidBody()->velocity.y = -getRigidBody()->velocity.y * elasticity;
		getTransform()->position.y += getRigidBody()->velocity.y * deltaTime;
		getRigidBody()->velocity.x *= 0.6;
		
		getRigidBody()->acceleration -= gravity;
	}
	// ceiling
	if (getTransform()->position.y <= 0 )
	{
		getRigidBody()->velocity.y = -getRigidBody()->velocity.y * elasticity;
		getTransform()->position.y += getRigidBody()->velocity.y * deltaTime;
		
		getRigidBody()->acceleration -= gravity;
	}

	// wall right
	if (getTransform()->position.x + getWidth() / 2 >= WALL)
	{
		getRigidBody()->velocity.x = -getRigidBody()->velocity.x * elasticity;
		getTransform()->position.x += getRigidBody()->velocity.x * deltaTime;
		
	}
	// wall left
	if (getTransform()->position.x - getWidth() / 2 <= 0)
	{
		getRigidBody()->velocity.x = -getRigidBody()->velocity.x * elasticity;
		getTransform()->position.x += getRigidBody()->velocity.x * deltaTime;
		
	}
}

void BouncyBall::m_reset()
{
	
}

float BouncyBall::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}


