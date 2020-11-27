#pragma once
#include "Bullet.h"
#include <vector>
#include "CollisionManager.h"
#include "Player.h"
#include "SoundManager.h"



class BulletPool
{
public:
	BulletPool(int);
	~BulletPool() = default;
	
	Bullet* Spawn();
	void Despawn(Bullet*);
	std::vector<Bullet*> all;
	void IsColliding(Player*);
	void SFX();
private:
	std::vector<Bullet*> active;
	std::vector<Bullet*> inactive;
};

