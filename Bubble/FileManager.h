#pragma once
#include <string>

class FileManager
{
public:
	FileManager(void);
	~FileManager(void);

	static FileManager& GetInstance();

	void LoadLevel(int _levelNum);

	void Save();
	void Load();

	void SetSaveNum(int saveNum) {FileManager::saveNum = saveNum;}

	void AdvanceLevel()	{currentLevel++;}

	void SetCurrentLevel(int currentLevel)	{FileManager::currentLevel = currentLevel;}
	int GetCurrentLevel()	{return currentLevel;}

private:
	void CreateObject(const std::string &ID, float x, float y);
	int saveNum;
	int currentLevel;
};