#include "obj_Player.h"
#include "GameObjectManager.h"
#include "AudioManager.h"

obj_Player::obj_Player()
{
	image = ImageManager::GetInstance().GetImage(0);
	S=0; O=0; A=0;
	velX = 0;
	velY = 0;
	SetID(PLAYER);
}
obj_Player::~obj_Player(void)
{
}

void obj_Player::Init(float x, float y, float velX, float velY, float volume)
{
	volume = 1500;
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
	S = sqrt( ((_mouseX)-(x))*((_mouseX)-(x)) + ((_mouseY) - (y))*((_mouseY)-(y)) );
	O = _mouseY - y ;
	A = _mouseX - x;

	//This part calculates the direction of the mouse, it needs some correction,  because inverted sin, cos and tan can have multiple awnsers and it will always return the
	//smallest, but not always the correct one.
	if(_mouseY < y)
		mouseDir = PI - acos(A/S) + PI;
	else 
		mouseDir = acos(A/S);

	if(_mouseButtonPressed[M_LEFT] && volume > 0)
	{
		GameObjectManager::GetInstance().SetPlaying(true);
		AudioManager::GetInstance().PlaySoundEffect(rand()%3+1);
		//Caclulate information about the other bubble that will be created
		float otherVolume = volume/75;
		float otherRadius = CalcRadius(otherVolume);
		float otherVelX = cos(mouseDir)*5;
		float otherVelY = sin(mouseDir)*5;
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
		GameObjectManager::GetInstance().CreateBubble(x + (radius+otherRadius)*(A/S),y +(radius+otherRadius)*(O/S), 
			otherVelX + velX, otherVelY + velY, otherVolume);
		//Change volume of the player's bubble
		volume -= otherVolume;
	}
	if(_mouseButtonPressed[M_RIGHT])
	{
		volume += 10000;
	}

	if(_keys[Q_KEY])
	{
		SetAlive(false);
	}

	if(volume != volumePrevious)
	{
		if(volume<=0)
			SetAlive(false);
		radius = CalcRadius(volume);
		circumference = CalcCircumference(radius);
	}

	if(velX != velXPrevious || velY !=velYPrevious)
	{
		float hypotenuse = sqrt( (velX*velX) + (velY*velY));
		float angle = 0;
		if(velY>0)
			angle = PI - acos(velY / hypotenuse) + PI;
		else
			angle = acos(velY / hypotenuse);
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
	if(!GameObjectManager::GetInstance().GetWon())
	{
		_camX = x;
		_camY = y;
	}
	
	volumePrevious = volume;
}
void obj_Player::Draw()
{
	//al_draw_filled_circle(x,y,radius,al_map_rgba(255,0,255,100));
	al_draw_scaled_rotated_bitmap(image, 104, 104, (x), (y), (1.0f/96.0f) * radius, (1.0f/96.0f) * radius, 0, 0);

	//al_draw_scaled_bitmap(image, 0, 0, 208, 208, x-(104*(1/96.f)*radius*(1/_zoom))-_camX, y-(104*(1/96.f)*radius*(1/_zoom))-_camY,208*(1/96.f)*radius*(1/_zoom),208*(1/96.f)*radius*(1/_zoom),0);


	//al_draw_filled_circle(x-_camX,y-_camY,radius,al_map_rgb(0,255,0));

	al_draw_line(x + (radius+5)*(A/S) , y + (radius+5)*(O/S), x + (radius+15)*(A/S) ,
		y + (radius+15)*(O/S) ,al_map_rgb(255,255,255),1);
	/*al_draw_line((x+(radius+5)*(A/S))*(1/_zoom) -_camX, (y+(radius+5)*(O/S))*(1/_zoom) -_camY, 
		(x+(radius+15)*(A/S))*(1/_zoom) -_camX, (y+(radius+15)*(O/S))*(1/_zoom) -_camY, al_map_rgb(255,255,255),1);
	*/
}
void obj_Player::Collided(GameObject *other)
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
