#pragma once
#ifndef __BRICK__
#define __BRICK__
#include "../src/UIControl.h"
#include "../src/CollisionManager.h"



class Brick final : public UIControl {
public:
	Brick();
	~Brick();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;


private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	
};


#endif /* defined (__BRICK__) */