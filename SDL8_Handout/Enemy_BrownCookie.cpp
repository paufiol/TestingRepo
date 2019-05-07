#include "Application.h"
#include "Path.h"
#include "Enemy_BrownCookie.h"
#include "ModuleCollision.h"

Enemy_BrownCookie::Enemy_BrownCookie(int x, int y) : Enemy(x, y)

{
	fPoint position(1, 1);

	fly.PushBack({  4, 72, 25, 25  });
	fly.PushBack({ 37 , 72, 25, 25 });
	fly.PushBack({ 69, 72, 25, 25 });
	fly.PushBack({ 101, 72, 25, 25 });
	fly.PushBack({ 134, 72, 25, 25 });
	fly.PushBack({ 170, 72, 25, 25 });
	fly.PushBack({ 203, 72, 25, 25 });
	fly.PushBack({ 236, 72, 25, 25 });
	fly.speed = 0.2f;

	animation = &fly;
	
	move.PushBack(position, 1, &fly);


	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_BrownCookie::Move(){

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}
		
	position.y = int(float(original_y) + 1);
	if(going_up) position.x += -1 + int(5.0f * sinf(wave));
	if (!going_up)  position.x += -1 + int(5.0f * sinf(wave));
}