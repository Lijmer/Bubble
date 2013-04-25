#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "globals.h"

class DisplayManager
{
public:
	DisplayManager(void);
	~DisplayManager(void);

	static DisplayManager& GetInstance();

	bool CreateDisplay();

	ALLEGRO_DISPLAY* GetDisplay()	{return display;}
	char GetState()					{return state;}

	void Clean();

	void ChangeState();

private:
	char state;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_TRANSFORM trans;
};

