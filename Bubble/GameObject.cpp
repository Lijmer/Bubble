#include "GameObject.h"

unsigned int GameObject::lastID = 0;

GameObject::GameObject(void)
{
	//Mostly setting a default values for all the variables
	x=0;
	y=0;
	z=0;
	velX=0;
	velY=0;
	volume = 0;
	volumePrevious = 0;
	radius = 0;

	ID=UNDEFINED;
	instanceID = ++lastID;
	alive = true;
}


GameObject::~GameObject(void)
{
}

void GameObject::Init(float x, float y, float velX, float velY)
{
	GameObject::x = x;
	GameObject::y = y;
	GameObject::velX = velX;
	GameObject::velY = velY;
}

void GameObject::Update()
{}
void GameObject::Draw()
{}

bool GameObject::CheckCollision(GameObject *other)
{
	float otherX = other->GetX();
	float otherY = other->GetY();
	float otherRadius = other->GetRadius();


	if((x-otherX)*(x-otherX) + (y-otherY)*(y-otherY) < (radius+otherRadius)*(radius+otherRadius))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameObject::Collided(GameObject *other)
{
	
}