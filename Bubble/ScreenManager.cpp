#include "ScreenManager.h"
#include "GameObjectManager.h"

ScreenManager::ScreenManager(void)
{
}


ScreenManager::~ScreenManager(void)
{
}

ScreenManager& ScreenManager::GetInstance()
{
	static ScreenManager instance;
	return instance;
}


void ScreenManager::ChangeLevel(int levelNum)
{
	//Destroy all objects
	GameObjectManager::GetInstance().DestroyAllObjects();

	
}

void ScreenManager::ChangeState(int state)
{
	if(state == MENU)
	{

	}
	else if(state == GAME)
	{

	}
}