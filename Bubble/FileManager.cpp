#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "DisplayManager.h"

#include "GameObjectManager.h"
FileManager::FileManager(void)
{
}


FileManager::~FileManager(void)
{
}


FileManager& FileManager::GetInstance()
{
	static FileManager instance;
	return instance;
}

void FileManager::LoadLevel()
{
	std::ifstream levelFile;
	levelFile.open("level/level1.lvl");
	if(!levelFile.is_open())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!",
			"FileManager", "Could not load level1.lvl", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
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
						else
						{
							CreateObject(temp, x*tileWidth, y*tileHeight);
							x++;
							temp="";
						}
					}
					x=0;
					y++;
				}
			}
		}
		else if((*iter) == "END")
			break;
	}	
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
		std::cout << "a" << tmp << std::endl;
		float volume = ::atof(tmp.c_str());
		GameObjectManager::GetInstance().CreateBubble(x,y,0,0,volume*1000);
		return;
	}
	found = tmp.find("b");
	if(found!=std::string::npos)
	{
		tmp.erase(found,1);
		std::cout << "b" << tmp << std::endl;
		float volume = ::atof(tmp.c_str());
		GameObjectManager::GetInstance().CreateAIBubble(x,y,0,0,volume*1000);
		return;
	}
	
}