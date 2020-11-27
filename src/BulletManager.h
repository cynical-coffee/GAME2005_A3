#pragma once
#include "Bullet.h"
#include "BulletPool.h"
#include "PlayScene.h"
class BulletManager
{
private:
	BulletPool* m_pPool;
	PlayScene* m_pPlayScene;

	float spawnTime = 3.0f;
	float timer;

public:
	BulletManager();
	void Update();
	void SpawnBullet();
};

