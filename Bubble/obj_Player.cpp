#include "obj_Player.h"

obj_Player::obj_Player(obj_Bubble* (*CreateBubble)(float x, float y, float velX, float velY, float volume))
{
	obj_Player::CreateBubble = CreateBubble;
	image = ImageManager::GetInstance().GetImage(0);
	S=0; O=0; A=0;
	velX = 0;
	velY = 0;
}

obj_Player::~obj_Player(void)
{
}

void obj_Player::Init(float x, float y, float velX, float velY, float volume)
{
	volume = 10000;
	obj_Player::x = x;
	obj_Player::y = y;
	obj_Player::velX = velX;
	obj_Player::velY = velY;
	obj_Player::volume = volume;
	volumePrevious = volume;
	radius = pow((float)volume,(float)(1.0/2.0))/PI;
}
void obj_Player::Update()
{
	S = sqrt( ((_mouseX+_camX)-(x))*((_mouseX+_camX)-(x)) + ((_mouseY+_camY) - (y))*((_mouseY+_camY)-(y)) );
	O = _mouseY+_camY - y ;
	A = _mouseX+_camX - x;

	//This part calculates the direction of the mouse, it needs some correction,  because inverted sin, cos and tan can have multiple awnsers and it will always return the
	//smalles, but not always the correct one.
	if(_mouseY < y-_camY)
		mouseDir = PI - acos(A/S) + PI;
	else 
		mouseDir = acos(A/S);

	if(_mouseButtonPressed[M_LEFT] && volume > 0)
	{
		velX += cos(mouseDir+PI)*(1/10.0f);
		velY += sin(mouseDir+PI)*(1/10.0f);
		CreateBubble(x + (radius+5)*(A/S),y +(radius+5)*(O/S),cos(mouseDir)*3, sin(mouseDir)*3, volume/30);
		volume -= volume/30;
	}
	if(_mouseButtonPressed[M_RIGHT])
		volume += 10000;

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

	//Set camera
	_camX = x - (_SCREEN_WIDTH/2.0);
	_camY = y - (_SCREEN_HEIGHT/2.0);
	_camX = 0;
	_camY = 0;

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
void obj_Player::Draw()
{
	al_draw_scaled_rotated_bitmap(image, 104, 104, x-_camX, y-_camY, (1.0/104.0) * radius, (1.0/104.0) * radius,0, 0);

	al_draw_line(x + (radius+5)*(A/S) -_camX, y + (radius+5)*(O/S) -_camY, x + (radius+15)*(A/S) -_camX, y + (radius+15)*(O/S) -_camY, al_map_rgb(255,255,255),1);
}
void obj_Player::Collided(GameObject *other)
{
	if(other->GetVolume() <= volume)
	{
		volume+=100;
	}
	else if(other->GetVolume() > volume)
	{
		volume-=100;
	}
}
