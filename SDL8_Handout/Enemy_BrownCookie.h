#ifndef __ENEMY_BROWNCOOKIE_H__
#define __ENEMY_BROWNCOOKIE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownCookie : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Path move;
	Animation fly;

public:

	Enemy_BrownCookie(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNCOOKIE_H__
