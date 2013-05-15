#include "GameObjectManager.h"

#include "globals.h"

#include "GameObject.h"
#include "obj_Bubble.h"
#include "obj_Player.h"
#include "obj_AI_Bubble.h"
#include "obj_Help_Text.h"

#include "obj_Menu_Button.h"

//Public:
GameObjectManager::GameObjectManager(void)
{
	won=false;
	lost=false;
	playing=false;
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
	std::vector<obj_Menu_Button*>::iterator btnIter;
	for(btnIter = buttons.begin(); btnIter!=buttons.end();)
	{
		delete (*btnIter);
		btnIter = buttons.erase(btnIter);
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
	obj_player->Init(_LEVEL_WIDTH/2,_LEVEL_HEIGHT/2,0,0,10000);
	pendingObjects.push_back(obj_player);
}
void GameObjectManager::TimerEvent()
{
	if(!paused)
	{
		Update();
		Collisions();
		Cleaning();

		//Check if won or lost
		if(!won && !lost && playing)
		{
			if(CheckWinningCondition())
			{
				CreateButton(250,300,obj_Menu_Button::MAIN_MENU);
				CreateButton(550,300,obj_Menu_Button::NEXT_LEVEL);
				won = true;
			}
			if(CheckLosingCondition())
			{
				CreateButton(250,300,obj_Menu_Button::MAIN_MENU);
				CreateButton(550,300,obj_Menu_Button::RETRY_LEVEL);
				lost = true;
			}
		}
		if((won || lost) && playing)
		{
			_camX=_SCREEN_WIDTH/2.0;
			_camY=_SCREEN_HEIGHT/2.0;
			_zoom = 1;
		}
	}
	else
	{
		UpdateButtons();
		Cleaning();
	}
}


void GameObjectManager::Pause()
{
	if(!paused && !won && !lost)
	{
		paused=true;
		CreateButton(250,300,obj_Menu_Button::MAIN_MENU);
		CreateButton(550,300,obj_Menu_Button::RESUME);
	}
	else if(paused)
	{
		paused=false;
		DestroyAllButtons();
	}
	else
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "", "", "", "",0);
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

	if(won)
	{
		al_draw_filled_rectangle(0, 0,_LEVEL_WIDTH, _LEVEL_HEIGHT, al_map_rgba(0,127,0,10));
	}
	if(lost)
	{
		al_draw_filled_rectangle(0, 0,_LEVEL_WIDTH, _LEVEL_HEIGHT, al_map_rgba(127,0,0,10));
	}


	std::vector<obj_Menu_Button*>::iterator btnIter;
	if(buttons.size()>0)
	{
		for(btnIter = buttons.begin(); btnIter!=buttons.end(); btnIter++)
		{
			(*btnIter)->Draw();
		}
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
void GameObjectManager::CreateButton(float x, float y, int kind)
{
	obj_menu_button = new obj_Menu_Button();
	obj_menu_button->Init(x,y,kind);
	buttons.push_back(obj_menu_button);
}
void GameObjectManager::CreateHelpTextObject(float x, float y)
{
	obj_help_text = new obj_Help_Text;
	obj_help_text->Init(x,y);
	objects.push_back(obj_help_text);
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
GameObject* GameObjectManager::GetClosestBubble(float x, float y, unsigned int instanceID, std::vector<unsigned int> &exceptions)
{
	GameObject* closestBubble=NULL;
	float smallestDistanceSquared = FLT_MAX;
	bool cont=true;
	for(getClosestBubbleIter = objects.begin(); getClosestBubbleIter!=objects.end(); getClosestBubbleIter++)
	{
		if((*getClosestBubbleIter)->GetInstanceID() == instanceID)
			continue;
		for(uintIter = exceptions.begin(); uintIter!=exceptions.end(); uintIter++)
		{
			if((*uintIter) == (*getClosestBubbleIter)->GetInstanceID())
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

void GameObjectManager::DestroyAllObjects()
{
	std::vector<GameObject *>::iterator iter;
	for(iter=objects.begin(); iter!=objects.end(); iter++)
	{
		(*iter)->SetAlive(false);
	}
	for(iter=pendingObjects.begin(); iter!=pendingObjects.end(); iter++)
	{
		(*iter)->SetAlive(false);
	}
	std::vector<obj_Menu_Button *>::iterator btnIter;
	for(btnIter=buttons.begin(); btnIter!=buttons.end(); btnIter++)
	{
		(*btnIter)->SetAlive(false);
	}
	obj_Menu_Button::SetNumButtons(0);
	obj_Menu_Button::SetSelectedButton(1);
}
void GameObjectManager::DestroyAllButtons()
{
	std::vector<obj_Menu_Button *>::iterator btnIter;
	for(btnIter=buttons.begin(); btnIter!=buttons.end(); btnIter++)
	{
		(*btnIter)->SetAlive(false);
	}
	obj_Menu_Button::SetNumButtons(0);
	obj_Menu_Button::SetSelectedButton(1);
}

float GameObjectManager::TimesBiggerThanPlayer(float volume)
{
	return volume/GetPlayerVolume();
}

bool GameObjectManager::CheckWinningCondition()
{
	std::vector<GameObject *>::iterator iter;
	float totalVolume=0;
	for(iter=objects.begin(); iter!=objects.end(); iter++)
	{
		if((*iter)->GetID() != PLAYER)
		{
			totalVolume+=(*iter)->GetVolume();
		}
	}
	if(GetPlayerVolume() > totalVolume)
		return true;
	else
		return false;
}
bool GameObjectManager::CheckLosingCondition()
{
	bool playerExists=false;
	std::vector<GameObject *>::iterator iter;
	for(iter=objects.begin(); iter!=objects.end(); iter++)
	{
		if((*iter)->GetID() == PLAYER)
		{
			playerExists = true;
			break;
		}
	}
	return !playerExists;
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
	std::vector<obj_Menu_Button*>::iterator btnIter;
	if(buttons.begin()!=buttons.end())
	{
		for(btnIter = buttons.begin(); btnIter!=buttons.end(); btnIter++)
		{
			(*btnIter)->Update();
			(*btnIter)->SetSelected(false);
		}
		buttons[obj_Menu_Button::GetSelectedButton()-1]->SetSelected(true);
		
		if(_keys_pressed[DOWN])
			obj_Menu_Button::NextButton();
		if(_keys_pressed[UP])
			obj_Menu_Button::PreviousButton();
		if(_keys_pressed[ENTER] && !_keys[ALT])
			buttons[obj_Menu_Button::GetSelectedButton()-1]->Execute();
		buttons[obj_Menu_Button::GetSelectedButton()-1]->UpdateClicked();
	}
}
inline void GameObjectManager::UpdateButtons()
{
	std::vector<obj_Menu_Button*>::iterator btnIter;
	if(buttons.begin()!=buttons.end())
	{
		for(btnIter = buttons.begin(); btnIter!=buttons.end(); btnIter++)
		{
			(*btnIter)->Update();
			(*btnIter)->SetSelected(false);
		}
		buttons[obj_Menu_Button::GetSelectedButton()-1]->SetSelected(true);
		
		if(_keys_pressed[DOWN])
			obj_Menu_Button::NextButton();
		if(_keys_pressed[UP])
			obj_Menu_Button::PreviousButton();
		if(_keys_pressed[ENTER] && !_keys[ALT])
			buttons[obj_Menu_Button::GetSelectedButton()-1]->Execute();
		buttons[obj_Menu_Button::GetSelectedButton()-1]->UpdateClicked();
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
	std::vector<obj_Menu_Button*>::iterator btnIter;
	for(btnIter=buttons.begin(); btnIter!=buttons.end(); )
	{
		if(!(*btnIter)->GetAlive())
		{
			delete (*btnIter);
			btnIter = buttons.erase(btnIter);
		}
		else
			btnIter++;
	}
}
