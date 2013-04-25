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
	radius = CalcRadius(volume);
	circumference = CalcCircumference(radius);
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
		radius = CalcRadius(volume);
		circumference = CalcCircumference(radius);
		float energyVelX = CalcEnergyKinetic(velX, volumePrevious);
		float energyVelY = CalcEnergyKinetic(velY, volumePrevious);
		if(velX >= 0)
			velX = CalcVelocity(energyVelX,volume);
		else
			velX = -CalcVelocity(energyVelX,volume);
		if(velY >= 0)
			velY = CalcVelocity(energyVelY,volume);
		else
			velY = -CalcVelocity(energyVelY,volume);
	}

	volumePrevious = volume;
}
void obj_Bubble::Draw()
{
	al_draw_scaled_rotated_bitmap(image, 104, 104, x-_camX, y-_camY, (1.0f/104.0f)*radius, (1.0f/104.0f)*radius, 0 , 0);
	//al_draw_filled_circle(x-_camX,y-_camY,radius,al_map_rgb(255,0,0));
}
void obj_Bubble::Collided(GameObject *other)
{
	if(volume >= other->GetVolume())
	{
		volume+=other->GetCircumference();
	}
	else if(volume < other->GetVolume())
	{
		volume-=circumference;
	}
}
