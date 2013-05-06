#include "ScreenManager.h"


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
