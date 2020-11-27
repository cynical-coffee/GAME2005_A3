#include "Player.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()//: m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->load("../Assets/sprites/Ship_0.png", "Ship");

	auto size = TextureManager::Instance()->getTextureSize("Ship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	//m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Ship", x, y, 0, 255, true);
	
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	float dirMagnitude = Util::magnitude(m_direction);
	if (dirMagnitude > 0)
	{
		m_direction *= 1.0f / Util::magnitude(m_direction);
		getRigidBody()->acceleration = m_direction * ACCELERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0)
	{
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	}

	if (Util::magnitude(getRigidBody()->acceleration) < ACCELERATION)
	{
		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}


	getRigidBody()->velocity += getRigidBody()->acceleration;
	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{
}

void Player::moveLeft() {
	m_direction.x = -1;
}

void Player::moveRight() {
	m_direction.x = 1;
}

void Player::moveUp() {
	m_direction.y = -1;
}

void Player::moveDown() {
	m_direction.y = 1;
}

void Player::stopMovingX() {
	m_direction.x = 0;
}

void Player::stopMovingY()
{
	m_direction.y = 0;
}

bool Player::isColliding(GameObject* pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Player::getDistance(GameObject* pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}