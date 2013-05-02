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
	volume = 1000;
	obj_Player::x = x;
	obj_Player::y = y;
	obj_Player::velX = velX;
	obj_Player::velY = velY;
	obj_Player::volume = volume;
	volumePrevious = volume;
	radius = CalcRadius(volume);
	circumference = CalcCircumference(radius);
}
void obj_Player::Update()
{
	S = sqrt( ((_mouseX+_camX)-(x))*((_mouseX+_camX)-(x)) + ((_mouseY+_camY) - (y))*((_mouseY+_camY)-(y)) );
	O = _mouseY+_camY - y ;
	A = _mouseX+_camX - x;

	//This part calculates the direction of the mouse, it needs some correction,  because inverted sin, cos and tan can have multiple awnsers and it will always return the
	//smallest, but not always the correct one.
	if(_mouseY < y-_camY)
		mouseDir = PI - acos(A/S) + PI;
	else 
		mouseDir = acos(A/S);

	if(_mouseButtonPressed[M_LEFT] && volume > 0)
	{
		//Caclulate information about the other bubble that will be created
		float otherVolume = volume/150;
		float otherRadius = CalcRadius(otherVolume);
		float otherVelX = cos(mouseDir)*10;
		float otherVelY = sin(mouseDir)*10;
		float otherEnergyVelX = CalcEnergyKinetic(otherVelX, otherVolume);
		float otherEnergyVelY = CalcEnergyKinetic(otherVelY, otherVolume);
		//Change velocity based on the kinetic energy created by shooting the other bubble away
		if(otherVelX >= 0)
			velX -= CalcVelocity(otherEnergyVelX, volume);
		else
			velX += CalcVelocity(otherEnergyVelX, volume);
		if(otherVelY >0)
			velY -= CalcVelocity(otherEnergyVelY, volume);
		else
			velY += CalcVelocity(otherEnergyVelY, volume);
		//Create the bubble (using some of the info calculated earlier in this if statement)
		CreateBubble(x + (radius+otherRadius)*(A/S),y +(radius+otherRadius)*(O/S), otherVelX + velX, otherVelY + velY, otherVolume);
		//Change volume of the player's bubble
		volume -= otherVolume;
	}
	if(_mouseButtonPressed[M_RIGHT])
		volume += 10000;

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

	if(velX != velXPrevious || velY !=velYPrevious)
	{
		float hypotenuse = sqrt( (velX*velX) + (velY*velY));
		float angle = 0;
		if(velY>0)
			angle = PI - acos(velY / hypotenuse) + PI;
		else
			angle = acos(velY / hypotenuse);

		//frictionX = -cos(angle)*.01;
		//frictionY = -sin(angle)*.01;
		
		//std::cout << frictionX << "\t" << frictionY << std::endl;
	}
	
	
	velXPrevious = velX;
	velYPrevious = velY;
	
	velX -= frictionX;
	velY -= frictionY;

	if(velX < 0.01 && velX > -0.01)
		velX=0;
	if(velY < 0.01 && velY > -0.01)
		velY = 0;

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
	if(_camX < 0)
		_camX = 0;
	else if(_camX > _LEVEL_WIDTH - _SCREEN_WIDTH)
		_camX = _LEVEL_WIDTH - _SCREEN_WIDTH;
	if(_camY < 0)
		_camY = 0;
	else if(_camY > _LEVEL_HEIGHT - _SCREEN_HEIGHT)
		_camY = _LEVEL_HEIGHT - _SCREEN_HEIGHT;

	_camX = 0;
	_camY = 0;

	

	volumePrevious = volume;
}
void obj_Player::Draw()
{
	al_draw_scaled_rotated_bitmap(image, 104, 104, x-_camX, y-_camY, (1.0/104.0) * radius, (1.0/104.0) * radius,0, 0);
	//al_draw_filled_circle(x-_camX,y-_camY,radius,al_map_rgb(0,255,0));

	al_draw_line(x + (radius+5)*(A/S) -_camX, y + (radius+5)*(O/S) -_camY, x + (radius+15)*(A/S) -_camX, y + (radius+15)*(O/S) -_camY, al_map_rgb(255,255,255),1);
}
void obj_Player::Collided(GameObject *other)
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
