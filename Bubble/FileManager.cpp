#include "FileManager.h"


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
		level.push_back(temp);

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
		std::cout << (*iter) << std::endl;
		if((*iter) == "[properties]")
		{
			for(iter2 = iter+1; iter2!=level.end(); iter2++)
			{
				if((*iter2) == ";")
					break;
				else if(!(*iter2).find("lvlWidth = "))
				{
					temp = (*iter2);
					temp.erase(0,11);
					lvlWidth=atoi(temp.c_str());
				}
				else if(!(*iter2).find("lvlHeight = "))
				{
					temp = (*iter2);
					temp.erase(0,12);
					lvlHeight=atoi(temp.c_str());
				}
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
				std::cout << (*iter2) << std::endl;
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
					for(unsigned int i=0; i<(*iter2).size(); i++)
					{
						if((*iter2)[i] != ' ' && (*iter2)[i] != '|')
							temp += (*iter2)[i];
						else
						{
							if(temp=="-1")
							{} //temp == -1 is checked the most, because it is the most common
							else if(temp == "00")
							{}
							else if(temp == "--")
							{
								temp="";
								continue;
							}
							else
							{
								std::string error = "Unknown object ID: " + temp;
								al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", 
									"FileManager", error.c_str(), "ok", ALLEGRO_MESSAGEBOX_ERROR);
							}
							if(++x>=lvlWidth)
							{x=0; y++;}

							temp="";
						}
					}
			}
		}
		else if((*iter) == "END")
			break;
	}	
}