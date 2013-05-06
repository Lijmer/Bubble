#include "obj_AI_Bubble.h"
#include "GameObjectManager.h"
#include <allegro5/allegro_primitives.h>
#include "obj_Bubble.h"
class obj_Bubble;
obj_AI_Bubble::obj_AI_Bubble(void)
{
	image = ImageManager::GetInstance().GetImage(0);
	SetID(AI_BUBBLE);
	shootCount = rand()%50+10;
	hasFoundDirection=false;
	removeBubbleFromShotBubblesCount=300;
}
obj_AI_Bubble::~obj_AI_Bubble(void)
{
}

void obj_AI_Bubble::Init(float x, float y, float velX, float velY, float volume)
{
	obj_AI_Bubble::x = x;
	obj_AI_Bubble::y = y;
	obj_AI_Bubble::velX = velX;
	obj_AI_Bubble::velY = velY;
	obj_AI_Bubble::volume = volume;
	volumePrevious = volume;
	radius = CalcRadius(volume);
	circumference = CalcCircumference(radius);
}

void obj_AI_Bubble::Update()
{
	if(volume < 0)
		SetAlive(false);
	
	/*
	-Find out which bubble is closest (an AI bubble or player bubble)
	Find out if it is bigger than the other
	if it is bigger			-> move away
	else if it is smaller	-> move towards it
	*/

	float S;
	float ox;
	float oy;
	GameObject *closestBubble = GameObjectManager::GetInstance().GetClosestBubble(x,y,GetInstanceID(),shotBubbles);
	//It checks for volume/75 so it doesn't fly towards a bubble en when it shoots it is smaller
	if(closestBubble!=NULL)
	{
		if(volume-(volume/75) > closestBubble->GetVolume())
		{
			hasFoundDirection = true;
			std::cout << "Towards\n";
			ox = closestBubble->GetX();
			oy = closestBubble->GetY();
			S = sqrt( ((ox)-(x))*((ox)-(x)) + ((oy) - (y))*((oy)-(y)) );
			if(y < oy)
				destinationDirection=acos((ox-x)/S) + PI;
			else
				destinationDirection=PI - acos((ox-x)/S) + 2*PI;

		}
		else if(volume <= closestBubble->GetVolume() && closestBubble->GetVolume() > volume/70)
		{
			hasFoundDirection = true;
			std::cout << "Away\n";
			ox = closestBubble->GetX();
			oy = closestBubble->GetY();
			S = sqrt( (ox-x)*(ox-x) + (oy-y)*(oy-y) );
		
			if(y < oy)
				destinationDirection=acos((ox-x)/S);
			else
				destinationDirection=PI - acos((ox-x)/S) + PI;
		}
	}

	//Shoot a bubble once in 0.5 - 2 seconds
	if(hasFoundDirection)
	{
		if(--shootCount <= 0)
		{
			shootCount = rand()%100+60;

			float otherVolume = volume/75;
			float otherRadius = CalcRadius(otherVolume);
			float otherVelX = cos(destinationDirection)*5;
			float otherVelY = sin(destinationDirection)*5;
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
			obj_Bubble *shotBubble = GameObjectManager::GetInstance().CreateBubble(x + (radius+otherRadius)*cos(destinationDirection),
				y + (radius+otherRadius)*sin(destinationDirection),	otherVelX + velX, otherVelY + velY, otherVolume);
			shotBubbles.push_back(shotBubble);
			//Change volume of the player's bubble
			volume -= otherVolume;
		}
	}

	if(--removeBubbleFromShotBubblesCount<=0)
	{
		removeBubbleFromShotBubblesCount=300;
		shotBubbles.erase(shotBubbles.begin());
	}


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

	volumePrevious = volume;
	hasFoundDirection = false;
}

void obj_AI_Bubble::Draw()
{
	al_draw_scaled_rotated_bitmap(image, 104, 104, x-_camX, y-_camY, (1.0f/104.0f) * radius, (1.0f/104.0f) * radius,0, 0);
	al_draw_filled_circle(x,y,radius,al_map_rgb(255,0,0));
}

void obj_AI_Bubble::Collided(GameObject *other)
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