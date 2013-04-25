#include "obj_Test.h"


obj_Test::obj_Test(void)
{
}


obj_Test::~obj_Test(void)
{
}

void obj_Test::Init(float x, float y)
{
	obj_Test::x = x;
	obj_Test::y = y;
}


void obj_Test::Update()
{
	if(_keys[UP])
		y-=9;
	if(_keys[DOWN])
		y+=9;
	if(_keys[LEFT])
		x-=9;
	if(_keys[RIGHT])
		x+=9;

	if(x<10)
		x=10;
	if(x>_LEVEL_WIDTH-10)
		x=_LEVEL_WIDTH-10;
	if(y<10)
		y=10;
	if(y>_LEVEL_HEIGHT-10)
		y=_LEVEL_HEIGHT-10;

}

void obj_Test::Draw()
{
	al_draw_filled_rectangle(x-8-_camX,y-8-_camY,x+8-_camX,y+8-_camY,al_map_rgb(255,255,0));
}