#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet() {
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(700.0f, 300.0f);
	setType(ENEMY);
	Reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw() {
	if (active)
	{
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
	}
	
}

void Bullet::update() {
	if (active)
	{
		const float deltaTime = 1.0f / 60.0f;

		getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
	}
}

void Bullet::clean() {

}

void Bullet::Reset()
{
	//active = false;
	getRigidBody()->velocity = glm::vec2(0.0f, 50.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
	getRigidBody()->isColliding = false;
}
