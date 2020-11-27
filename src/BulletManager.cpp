#include "BulletManager.h"

BulletManager::BulletManager()
{
	
}

void BulletManager::Update()
{
	if( timer >= spawnTime)
	{
		SpawnBullet();
	}
}

void BulletManager::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
		m_pPlayScene->addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, rand() % 100 * -1);
	}
}
