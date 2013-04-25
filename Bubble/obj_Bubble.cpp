#include "obj_Bubble.h"

obj_Bubble::obj_Bubble(void)
{
	image = ImageManager::GetInstance().GetImage(0);
}
obj_Bubble::~obj_Bubble(void)
{
}

void obj_Bubble::Init(float x, float y, float velX, float velY, float volume)
{
	obj_Bubble::x = x;
	obj_Bubble::y = y;
	obj_Bubble::velX = velX;
	obj_Bubble::velY = velY;
	obj_Bubble::volume = volume;
	volumePrevious = volume;
	radius = pow((float)volume,(float)(1.0/2.0))/PI;
}
void obj_Bubble::Update()
{
	if(volume < 0)
		setAlive(false);

	x+=velX;
	y+=velY;

	if(x<radius)
	{
		velX = -(velX);
		x=radius;
	}
	else if(x>_LEVEL_WIDTH - radius)
	{
		velX = -(velX);
		x = _LEVEL_WIDTH - radius;
	}
	if(y<radius)
	{
		velY = -(velY);
		y=radius;
	}
	else if(y>_LEVEL_HEIGHT - radius)
	{
		velY = -(velY);
		y = _LEVEL_HEIGHT - radius;
	}

	if(volume != volumePrevious)
	{
		radius = pow((float)volume,(float)(1.0/2.0))/PI;
		float energyVelX = .5*volumePrevious*(velX*velX);
		float energyVelY = .5*volumePrevious*(velY*velY);
		if(velX >= 0)
			velX = sqrt(energyVelX/(.5*volume));
		else
			velX = -sqrt(energyVelX/(.5*volume));
		if(velY >= 0)
			velY = sqrt(energyVelY/(.5*volume));
		else
			velY = -sqrt(energyVelY/(.5*volume));
	}

	volumePrevious = volume;
}
void obj_Bubble::Draw()
{
	al_draw_scaled_rotated_bitmap(image, 104, 104, x-_camX, y-_camY, (1.0f/104.0f)*radius, (1.0f/104.0f)*radius, 0 , 0);
}
void obj_Bubble::Collided(GameObject *other)
{
	if(other->GetVolume() < volume)
	{
		volume+=100;
	}
	else if(other->GetVolume() > volume)
	{
		volume-=100;
	}
}
