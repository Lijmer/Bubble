#pragma once
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
class obj_Test
{
public:
	obj_Test(void);
	~obj_Test(void);

	void Init(float x, float y);
	void Update();
	void Draw();

	float getX()	{return x;}
	float getY()	{return y;}

private:
	float x;
	float y;
	float velX;
	float velY;
};

