#include "GameObjectManager.h"

#include "globals.h"

#include "GameObject.h"
#include "obj_Bubble.h"
#include "obj_Player.h"
#include "obj_AI_Bubble.h"

#include <iostream>
//Public:
GameObjectManager::GameObjectManager(void)
{
}
GameObjectManager::~GameObjectManager(void)
{
	for(objectsIter = objects.begin(); objectsIter!=objects.end(); )
	{
		delete (*objectsIter);
		objectsIter = objects.erase(objectsIter);
	}
	for(pendingObjectsIter = pendingObjects.begin(); pendingObjectsIter!=pendingObjects.end();)
	{
		delete (*pendingObjectsIter);
		pendingObjectsIter = pendingObjects.erase(pendingObjectsIter);
	}
}

GameObjectManager& GameObjectManager::GetInstance()
{
	static GameObjectManager instance;
	return instance;
}
void GameObjectManager::Create()
{
	obj_player = new obj_Player;
	obj_player->Init(_SCREEN_WIDTH/2,_SCREEN_HEIGHT/2,0,0,10000);
	pendingObjects.push_back(obj_player);
}
void GameObjectManager::TimerEvent()
{
	Update();
	Collisions();
	Cleaning();
}

float GameObjectManager::GetPlayerVolume()
{
	if(obj_player!=NULL)
		return obj_player->GetVolume();
	else
		return -1;
}

void GameObjectManager::Draw()
{
	for(objectsIter=objects.begin(); objectsIter!=objects.end(); objectsIter++)
	{
		(*objectsIter)->Draw();
	}
}

obj_Bubble* GameObjectManager::CreateBubble(float x, float y, float velX, float velY, float volume)
{
	obj_bubble = new obj_Bubble();
	obj_bubble->Init(x,y,velX,velY,volume);
	pendingObjects.push_back(obj_bubble);
	return obj_bubble;
}
obj_AI_Bubble* GameObjectManager::CreateAIBubble(float x, float y, float velX, float velY, float volume)
{
	obj_ai_bubble = new obj_AI_Bubble();
	obj_ai_bubble->Init(x,y,velX,velY,volume);
	pendingObjects.push_back(obj_ai_bubble);
	return obj_ai_bubble;
}
GameObject* GameObjectManager::GetClosestBubble(float x, float y, unsigned int instanceID)
{
	GameObject* closestBubble=NULL;
	float smallestDistanceSquared = FLT_MAX;
	for(getClosestBubbleIter = objects.begin(); getClosestBubbleIter!=objects.end(); getClosestBubbleIter++)
	{
		if((*getClosestBubbleIter)->GetInstanceID() == instanceID)
			continue;
		float ox = (*getClosestBubbleIter)->GetX();
		float oy = (*getClosestBubbleIter)->GetY();
		float distanceSquared = ((x-ox)*(x-ox)) + ((y-oy)*(y-oy));
		if(distanceSquared < smallestDistanceSquared)
		{
			smallestDistanceSquared = distanceSquared;
			closestBubble = (*getClosestBubbleIter);
		}
	}
	return closestBubble;
}
GameObject* GameObjectManager::GetClosestBubble(float x, float y, unsigned int instanceID, std::vector<GameObject*> &exceptions)
{
	GameObject* closestBubble=NULL;
	float smallestDistanceSquared = FLT_MAX;
	bool cont=true;
	for(getClosestBubbleIter = objects.begin(); getClosestBubbleIter!=objects.end(); getClosestBubbleIter++)
	{
		if((*getClosestBubbleIter)->GetInstanceID() == instanceID)
			continue;
		for(getClosestBubbleIter2 = exceptions.begin(); getClosestBubbleIter2!=exceptions.end(); getClosestBubbleIter2++)
		{
			if((*getClosestBubbleIter2)->GetInstanceID() == (*getClosestBubbleIter)->GetInstanceID())
				cont=false;
		}
		if(!cont)
			continue;
		float ox = (*getClosestBubbleIter)->GetX();
		float oy = (*getClosestBubbleIter)->GetY();
		float distanceSquared = ((x-ox)*(x-ox)) + ((y-oy)*(y-oy));
		if(distanceSquared < smallestDistanceSquared)
		{
			smallestDistanceSquared = distanceSquared;
			closestBubble = (*getClosestBubbleIter);
		}
	}
	return closestBubble;
}
//Private
inline void GameObjectManager::Update()
{
	for(objectsIter = objects.begin(); objectsIter!= objects.end(); objectsIter++)
	{
		(*objectsIter)->Update();
	}
	//This pushes all objects that were created in the update event to the objects vector
	for(pendingObjectsIter = pendingObjects.begin(); pendingObjectsIter!=pendingObjects.end(); )
	{
		objects.push_back(*pendingObjectsIter);
		pendingObjectsIter = pendingObjects.erase(pendingObjectsIter);
	}
}
inline void GameObjectManager::Collisions()
{
	for(objectsIter = objects.begin(); objectsIter!=objects.end(); objectsIter++)
	{
		for(objectsIter2=objectsIter; objectsIter2!=objects.end(); objectsIter2++)
		{
			if(((*objectsIter)->GetInstanceID() == (*objectsIter2)->GetInstanceID()))
				continue;
			if((*objectsIter)->CheckCollision(*objectsIter2))
			{
				(*objectsIter)->Collided(*objectsIter2);
				(*objectsIter2)->Collided(*objectsIter);
			}
		}
	}
}
inline void GameObjectManager::Cleaning()
{
	//Delete all objects where alive==false
	for(objectsIter = objects.begin(); objectsIter!=objects.end();)
	{
		if(!(*objectsIter)->GetAlive())
		{
			delete (*objectsIter);
			objectsIter = objects.erase(objectsIter);
		}
		else
			objectsIter++;
	}
}