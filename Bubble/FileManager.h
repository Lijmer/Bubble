#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "DisplayManager.h"
class FileManager
{
public:
	FileManager(void);
	~FileManager(void);

	static FileManager& GetInstance();

	void LoadLevel();
};