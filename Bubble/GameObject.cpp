#include "GameObject.h"

unsigned int GameObject::lastID = 0;

//Public functions*************************************************************

GameObject::GameObject(void)
{
	//Mostly setting a default values for all the variables
	x=0;
	y=0;
	z=0;
	velX=0;
	velY=0;
	velXPrevious = 0;
	velYPrevious = 0;
	volume = 0;
	volumePrevious = 0;
	radius = 0;
	circumference = 0;
	frictionX = 0;
	frictionY = 0;

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

//Protected functions**********************************************************

float GameObject::CalcRadius(float volume)
{
	return (pow((float)volume/PI,(float)(1.0/2.0)));
}
float GameObject::CalcCircumference(float radius)
{
	return (2*PI*radius);
}
float GameObject::CalcEnergyKinetic(float velocity, float mass)
{
	return (.5*mass*(velocity*velocity));
}
float GameObject::CalcVelocity(float energyKinetic, float mass)
{
	return sqrt((2*energyKinetic)/mass);
}
float GameObject::CalcCenterAngleTriangleInCirlce(float x1, float y1, float x2, float y2, float x3, float y3)
{
	//A^2 + B^2 = C^2
	float a = sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
	float b = sqrt(((x2-x3)*(x2-x3)) + ((y2-y3)*(y2-y3)));
	float c = sqrt(((x3-x1)*(x3-x1)) + ((y3-y1)*(y3-y1)));
	
	//angleA is the angle at (x1,y1)
	return acos(((b*b) + (c*c) - (a*a))/(2*b*c));
}
