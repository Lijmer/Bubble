#include "DisplayManager.h"

#include <allegro5/allegro_native_dialog.h>

#include "globals.h"


DisplayManager::DisplayManager(void)
{
	display = NULL;
	state = WINDOWED;
}


DisplayManager::~DisplayManager(void)
{
	al_destroy_display(display);
}


DisplayManager& DisplayManager::GetInstance()
{
	static DisplayManager instance;
	return instance;
}

bool DisplayManager::CreateDisplay()
{
	//Create new display, it gets scaled to full screen
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_REQUIRE);
	display = al_create_display(_SCREEN_WIDTH,_SCREEN_HEIGHT);

	//Setting the width and height of the monitor to a global variable, so other functions can use it (MoveCam() for example)
	_monitorWidth = disp_data.width;
	_monitorHeight = disp_data.height;

	//Calculate the scale, the screen will get scaled to the smallest one (no stretching), it is saved in scaleScreen.
	float scaleScreenX = disp_data.width / (float)_SCREEN_WIDTH;
	float scaleScreenY = disp_data.height / (float)_SCREEN_HEIGHT;
	_scaleScreen = min(scaleScreenX, scaleScreenY);
	//_startScaleScreen = _scaleScreen;

	//Stretches the display on the monitor
	al_set_target_backbuffer(display);
	al_identity_transform(&trans);
	al_scale_transform(&trans, 1, 1);
	al_translate_transform(&trans, 0, 0);
	al_use_transform(&trans);

	//Check if display is created, else return false
	if(!display)
	{
		al_show_native_message_box(display, "Error!", "DisplayManager", "Failed to create display", "OkSok", ALLEGRO_MESSAGEBOX_ERROR);
		return false;
	}

	//If everything went alright, return true
	return true;
}

void DisplayManager::ChangeState()
{
	//If fullscreen, change to windowed
	if(state == FULLSCREEN_WINDOW)
	{
		//Change state
		state = WINDOWED;


		al_resize_display(display, _SCREEN_WIDTH, _SCREEN_HEIGHT);
		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, false);

		//Make sure the window doesn't get stretched and moved.
		al_set_target_backbuffer(display);
		al_identity_transform(&trans);
		al_scale_transform(&trans, 1, 1);
		al_translate_transform(&trans, 0, 0);
		al_use_transform(&trans);
	}
	//If windowed, change to full screen
	else if(state == WINDOWED)
	{
		state = FULLSCREEN_WINDOW;

		al_resize_display(display, _SCREEN_WIDTH, _SCREEN_HEIGHT);
		al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
		al_toggle_display_flag(display, ALLEGRO_NOFRAME, true);

		//Stretches the display on the monitor
		al_set_target_backbuffer(display);
		al_identity_transform(&trans);
		al_scale_transform(&trans, _scaleScreen, _scaleScreen);
		al_translate_transform(&trans, (_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0, (_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0);
		al_use_transform(&trans);

		if(!display)
			al_show_native_message_box(display, "Error!", "DisplayManager", "Failed to create display", "OkSok", ALLEGRO_MESSAGEBOX_ERROR);
	}
}

void DisplayManager::Transform()
{
	if(state == WINDOWED)
	{/*
		al_identity_transform(&trans);
		al_translate_transform(&trans, -_SCREEN_WIDTH/2.0f, -_SCREEN_HEIGHT/2.0f);
		al_scale_transform(&trans, 1/_zoom, 1/_zoom);
		al_translate_transform(&trans, -(_camX-_SCREEN_WIDTH/2.0f), -(_camY-_SCREEN_HEIGHT/2.0f));
		al_use_transform(&trans);
		*/
		al_identity_transform(&trans);
		//al_translate_transform(&trans, -(_camX - (_SCREEN_WIDTH/2.0f)), -(_camY - (_SCREEN_HEIGHT/2.0f)));
		al_translate_transform(&trans, -_camX, -_camY);
		al_scale_transform(&trans, 1/_zoom, 1/_zoom);
		al_translate_transform(&trans, _SCREEN_WIDTH/2.0f, _SCREEN_HEIGHT/2.0f);
		al_use_transform(&trans);
	}
	else if(state == FULLSCREEN_WINDOW)
	{
		al_identity_transform(&trans);
		/*al_translate_transform(&trans, -_SCREEN_WIDTH/2.0f, -_SCREEN_HEIGHT/2.0f);
		al_scale_transform(&trans, 1/_zoom, 1/_zoom);
		al_translate_transform(&trans, -(_camX-_SCREEN_WIDTH/2.0f), -(_camY-_SCREEN_HEIGHT/2.0f));*/
		al_translate_transform(&trans, -_camX, -_camY);
		al_scale_transform(&trans, 1/_zoom, 1/_zoom);
		al_translate_transform(&trans, _SCREEN_WIDTH/2.0f, _SCREEN_HEIGHT/2.0f);
		al_scale_transform(&trans, _scaleScreen, _scaleScreen);
		al_translate_transform(&trans, (_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0, (_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0);
		al_use_transform(&trans);
	}
}