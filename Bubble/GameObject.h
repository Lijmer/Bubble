#pragma once
#include "globals.h"

#include "ImageManager.h"

#include <math.h>

#include <iostream>
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);
	void Init(float x, float y, float velX, float velY);
	void virtual Update();
	void virtual Draw();

	void virtual Collided(GameObject *other);

	bool CheckCollision(GameObject *other);

	float GetX()							{return x;}
	float GetY()							{return y;}
	int GetZ()								{return z;}
	float GetVelX()							{return velX;}
	float GetVelY()							{return velY;}
	float GetVolume()						{return volume;}
	float GetRadius()						{return radius;}
	int GetID()								{return ID;}
	unsigned int GetInstanceID()			{return instanceID;}
	bool getAlive()							{return alive;}

	void SetX(float x)						{GameObject::x = x;}
	void SetY(float y)						{GameObject::y = y;}
	void SetZ(int z)						{GameObject::z = z;}
	void SetVelX(float velX)				{GameObject::velX = velX;}
	void SetVelY(float velY)				{GameObject::velY = velY;}
	void SetVolume(float volume)			{GameObject::volume = volume;}
	void SetID(int ID)						{GameObject::ID = ID;}
	void setAlive(bool alive)				{GameObject::alive = alive;}


protected:
	float x;
	float y;
	int z;
	float velX;
	float velY;
	float volume;
	float volumePrevious;
	float radius;

	ALLEGRO_BITMAP *image;
private:
	bool alive;
	int ID;
	unsigned int instanceID;
	static unsigned int lastID;
};
