#include "obj_Bubble.h"

#include "GameObjectManager.h"

obj_Bubble::obj_Bubble(void)
{
	image = ImageManager::GetInstance().GetImage(0);
	imageRed = ImageManager::GetInstance().GetImage(1);
	imageGreen = ImageManager::GetInstance().GetImage(2);
	SetID(BUBBLE);
	r=0, g=0, b=0;
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
		SetAlive(false);

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
		/*float energyVelX = CalcEnergyKinetic(velX, volumePrevious);
		float energyVelY = CalcEnergyKinetic(velY, volumePrevious);
		if(velX >= 0)
			velX = CalcVelocity(energyVelX,volume);
		else
			velX = -CalcVelocity(energyVelX,volume);
		if(velY >= 0)
			velY = CalcVelocity(energyVelY,volume);
		else
			velY = -CalcVelocity(energyVelY,volume);
		*/
	}

	if(GameObjectManager::GetInstance().TimesBiggerThanPlayer(volume)>1)
	{
		r+=3;
		g-=3;
		if(r>50)
			r=50;
		if(g<0)
			g=0;
	}
	else
	{
		g+=3;
		r-=3;
		if(g>50)
			g=50;
		if(r<0)
			r=0;
	}

	volumePrevious = volume;
}
void obj_Bubble::Draw()
{
	//al_draw_filled_circle(x,y,radius,al_map_rgba(r,g,b,1));
	al_draw_tinted_scaled_rotated_bitmap(imageRed,al_map_rgba(r,r,r,r),104,104,x,y,(1/96.f)*radius,(1/96.f)*radius,0,0);
	al_draw_tinted_scaled_rotated_bitmap(imageGreen,al_map_rgba(g,g,g,g),104,104,x,y,(1/96.f)*radius,(1/96.f)*radius,0,0);
	al_draw_scaled_rotated_bitmap(image,104,104,x,y,(1/96.f)*radius,(1/96.f)*radius,0,0);
	//al_draw_scaled_rotated_bitmap(image, 104, 104,(x)*(1/_zoom)-_camX, (y)*(1/_zoom)-_camY, (1.0f/96.0f)*radius, (1.0f/96.0f)*radius, 0 , 0);
	//al_draw_scaled_bitmap(image, 0, 0, 208, 208, (x-(104*(1/96.f)*radius*(1/_zoom)))*(1/_zoom)-_camX, (y-(104*(1/96.f)*radius*(1/_zoom)))-_camY*(1/_zoom),208*(1/96.f)*radius*(1/_zoom),208*(1/96.f)*radius*(1/_zoom),0);
}
void obj_Bubble::Collided(GameObject *other)
{
	if(volume >= other->GetVolume())
	{
		volume+=other->GetCircumference()*2;
	}
	else if(volume < other->GetVolume())
	{
		volume-=circumference*2;
	}
}