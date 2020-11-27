#include "BulletPool.h"

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; ++i)
	{
		Bullet* bullet = new Bullet();
		inactive.push_back(bullet);
		all.push_back(bullet);
	}
}

Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (!inactive.empty())
	{
		bullet = inactive.back();
		bullet->Reset();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		std::cout << "Spawned." << std::endl;
		std::cout << " Active Count " << std::to_string(active.size()) << std::endl;
	}
	else
	{
		std::cout << "ERROR: Bullet could not be spawned. Max bullets spawned." <<std::endl;
	}
	return bullet;
	
}

void BulletPool::Despawn(Bullet* bullet)
{
	//bullet->Reset();
	bullet->active = false;
	inactive.push_back(bullet);
	for (auto myIter = active.begin(); myIter != active.end(); myIter++)
	{
		if(*myIter == bullet)
		{
			active.erase(myIter);
			std::cout << "Despawned" << std::endl;
			std::cout << " Active Count " << std::to_string(active.size()) << std::endl;
			return;
		}
	}
}

void BulletPool::IsColliding(Player* player)
{
	for (unsigned int i = 0; i < active.size(); ++i)
	{
		if (CollisionManager::circleAABBCheck(player, active[i]))
		{
			std::cout << "Collision." << std::endl;
			this->SFX();
		}
	}
	
}

void BulletPool::SFX()
{
	SoundManager::Instance().load("../Assets/audio/Explosion.wav", "Thunder", SOUND_SFX);
	SoundManager::Instance().playSound("Thunder", 0, -1);
}


