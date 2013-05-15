#include "FileManager.h"

#include "globals.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "DisplayManager.h"

#include "GameObjectManager.h"
FileManager::FileManager(void)
{
	//Variable initialization
	saveNum=-1;

	//Create a save file if it doensn't exists
	std::fstream saveFile;
	saveFile.open("save/save.sav");
	if(!saveFile.is_open())
	{
		std::ofstream createSaveFile;
		createSaveFile.open("save/save.sav");
		//Add default data for save file
		std::string defSave = "0,10;";
		createSaveFile << defSave << std::endl << defSave << std::endl << defSave << std::endl;
		createSaveFile.close();
		saveFile.open("save/save.sav");
	}
	if(!saveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", 
		"FileManager", "Couldn't open/create save file", "ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
	
}

FileManager::~FileManager(void)
{
}

FileManager& FileManager::GetInstance()
{
	static FileManager instance;
	return instance;
}

void FileManager::LoadLevel(int _levelNum)
{
	std::ifstream levelFile;
	
	if(_levelNum==LVL_MENU)
		levelFile.open("level/menu.lvl");
	else if(_levelNum==LVL_NEW_GAME)
		levelFile.open("level/new_game.lvl");
	else if(_levelNum==LVL_LOAD_GAME)
		levelFile.open("level/load_game.lvl");
	else if(_levelNum==LVL_OPTIONS)
		levelFile.open("level/options.lvl");
	else if(_levelNum==LVL_HELP)
		levelFile.open("level/help.lvl");
	else if(_levelNum==LVL_1)
		levelFile.open("level/level1.lvl");
	else if(_levelNum==LVL_2)
		levelFile.open("level/level2.lvl");
	else if(_levelNum==LVL_3)
		levelFile.open("level/level3.lvl");
	else if(_levelNum==LVL_4)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Finished", "congratulations",
			"You have beated the last level of the alpha version. For now there are just 3 levels.", "ok", 0);
		GameObjectManager::GetInstance().DestroyAllObjects();
		LoadLevel(LVL_MENU);
		return;
	}

	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!",
			"FileManager", "Could not load level file", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	std::string temp;
	std::vector<std::string> level;
	std::vector<std::string>::iterator iter;
	std::vector<std::string>::iterator iter2;

	int lvlWidth=0, lvlHeight=0, tileWidth=0, tileHeight=0;

	while(std::getline(levelFile,temp))
	{
		unsigned found = temp.find("//");
		if(found!=std::string::npos)	
			temp.erase(found);
		level.push_back(temp);
	}
	temp="";

	levelFile.close();
	if(levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!",
			"FileManager", "Could not close level1.lvl", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}

	for(iter = level.begin(); iter!=level.end(); iter++)
	{
		//std::cout << (*iter) << std::endl;
		if((*iter) == "[properties]")
		{
			for(iter2 = iter+1; iter2!=level.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else if(!(*iter2).find("tileWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					tileWidth = atoi(temp.c_str());
				}
				else if(!(*iter2).find("tileHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,13);
					tileHeight = atoi(temp.c_str());
				}
			}
		}
		else if((*iter) == "[map]")
		{
			int x=0,y=0;
			int highestX=0, highestY=0;
			temp="";
			for(iter2 = iter+1; iter2!=level.end(); iter2++)
			{
				if((*iter2)==";")
					break;
				else
				{
					for(unsigned int i=0; i<(*iter2).size(); i++)
					{
						if((*iter2)[i] != ' ' && (*iter2)[i] != '|')
							temp += (*iter2)[i];
						else if(temp.length()>0)
						{
							if(temp == "--")
							{
								x=0;
								y--;
								temp="";
								break;
							}
							CreateObject(temp, x*tileWidth, y*tileHeight);
							x++;
							if(x>highestX)
								highestX=x;
							temp="";
						}
						else
						{
							x=0;
							y--;
							temp="";
							break;
						}
					}
					x=0;
					y++;
					if(y>highestY)
						highestY=y;
				}
			}
			_LEVEL_WIDTH = highestX*tileWidth;
			_LEVEL_HEIGHT = highestY*tileHeight;
		}
		else if((*iter) == "END")
			break;
	}
	if(_levelNum==LVL_1 || _levelNum==LVL_2 || _levelNum==LVL_3)
		GameObjectManager::GetInstance().Create();

	GameObjectManager::GetInstance().SetPlaying(false);
	GameObjectManager::GetInstance().SetWon(false);
	GameObjectManager::GetInstance().SetLost(false);
}

void FileManager::Save()
{
	//What do I want to save
	//SaveActive, Level
	std::ifstream isaveFile;
	isaveFile.open("save/save.sav");
	if(!isaveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), 
			"Error!", "FileManager", "Couldn't load save file", "ok", 0);
		return;
	}
	std::string temp;
	std::vector<std::string> save;
	std::vector<std::string>::iterator iter;

	//load the save file in memory
	while(getline(isaveFile, temp))
	{
		save.push_back(temp);
	}
	isaveFile.close();

	std::ofstream osaveFile;
	osaveFile.open("save/save.sav");

	std::stringstream ss;

	ss << 1 << "," << currentLevel;

	if(saveNum<1|| saveNum>3)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", "Illegal value for saveNum", "ok", 0);
		osaveFile.close();
		return;
	}

	save[saveNum-1] = ss.str();

	//clear the stringstream
	ss.clear();
	ss.str(std::string());

	for(iter = save.begin(); iter!=save.end(); iter++)
		ss << (*iter) << std::endl;

	osaveFile << ss.str();
	osaveFile.close();
}

void FileManager::Load()
{
	std::ifstream saveFile;
	saveFile.open("save/save.sav");
	if(!saveFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "FileManager", "Couldn't load save file", "ok", 0);
		return;
	}

	std::string temp;
	std::vector<std::string> save;
	std::vector<std::string>::iterator iter;

	while(getline(saveFile,temp))
	{
		save.push_back(temp);
	}
	saveFile.close();

	temp="";
	
	int valueNum=0;
	for(unsigned i=0; i<save[saveNum-1].size(); i++)
	{
		if(save[saveNum-1][i]==',' || save[saveNum-1][i] == ';')
		{
			switch(valueNum)
			{
			case 0:
				if(::atoi(temp.c_str())==0)
					return;
				break;
			case 1:
				currentLevel = ::atoi(temp.c_str());
				break;
			}
			valueNum++;
			temp="";
		}
		else
			temp += save[saveNum-1][i];
	}
	GameObjectManager::GetInstance().DestroyAllObjects();
	LoadLevel(currentLevel);
}

inline void FileManager::CreateObject(const std::string &ID, float x, float y)
{
	if(ID == "-1")
		return;
	std::string tmp = ID;
	unsigned found = tmp.find("a");
	if(found!=std::string::npos)
	{
		tmp.erase(found,1);
		float volume = ::atof(tmp.c_str());
		GameObjectManager::GetInstance().CreateBubble(x,y,0,0,volume*1000);
		return;
	}
	found = tmp.find("b");
	if(found!=std::string::npos)
	{
		tmp.erase(found,1);
		float volume = ::atof(tmp.c_str());
		GameObjectManager::GetInstance().CreateAIBubble(x,y,0,0,volume*1000);
		return;
	}
	found = tmp.find("m");
	if(found!=std::string::npos)
	{
		tmp.erase(found,1);
		GameObjectManager::GetInstance().CreateButton(x,y,::atoi(tmp.c_str()));
		return;
	}

	
}