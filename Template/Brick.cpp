#include "Brick.h"
#include "../src/TextureManager.h"



Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/rectangle.png", "brick");
	
	const auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(BRICK);
}

Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Brick
	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
	m_move();
	m_checkBounds();
}

void Brick::clean()
{
}

void Brick::m_move()
{
	
}

void Brick::m_checkBounds()
{
	
	
}

void Brick::m_reset()
{
}

