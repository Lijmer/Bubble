#pragma once
#include <string>

class FileManager
{
public:
	FileManager(void);
	~FileManager(void);

	static FileManager& GetInstance();

	void LoadLevel();

private:
	void CreateObject(const std::string &ID, float x, float y);
};