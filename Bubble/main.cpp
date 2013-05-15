#pragma region includes

//General
#include "globals.h"
#include "Exit.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

//Managers
#include "DisplayManager.h"
#include "ImageManager.h"
#include "FileManager.h"
#include "GameObjectManager.h"
#include "FontManager.h"
#include "AudioManager.h"

//Backgrounds
#include "Background.h"

#pragma endregion

#pragma region Prototypes
void MoveCam();
void UpdateMouseCoordinates(float mX, float mY);
obj_Bubble* CreateBubble(float x, float y, float velX, float velY, float volume);
#pragma endregion Contains declerations of functions later in this file

#pragma region main variables
ALLEGRO_EVENT_QUEUE *event_queue	= NULL;
ALLEGRO_TIMER *timer				= NULL;
//ALLEGRO_TRANSFORM camera;
ALLEGRO_BITMAP *buffer				= NULL;
ALLEGRO_MOUSE_CURSOR *cursor		= NULL;
#pragma endregion Declaring some variables for allegro. They are not in main(), because they need to be used in other functions in this file aswell

int main(int argc, char **argv)
{
	#pragma region Set-Up
	//Declaring variables for various stuff (most very important)
	float gameTime = 0;
	bool done = false;
	bool redraw = true;

	//init allegro, if failed the program will terminate
	if(!al_init())
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "Main", "Failed to initialize Allegro 5", "OkSok", ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create a display
	if(!DisplayManager::GetInstance().CreateDisplay())
		return -1;

	#pragma region Install addons
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	#pragma endregion install and init the addons (like sound, keyboard, mouse)

	//Initialize the image manager, this will load all the images into the memory and will give error messages if anything goes wrong
	ImageManager::GetInstance().Init();
	FontManager::GetInstance().Init();
	
	#pragma region Create ALL the objects

	FileManager::GetInstance().LoadLevel(LVL_MENU);
	
	Background background;
	#pragma endregion

	//create event_queue and the timer
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	buffer = al_create_bitmap(_SCREEN_WIDTH,_SCREEN_HEIGHT);
	
	#pragma region Register Event Sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(DisplayManager::GetInstance().GetDisplay()));
	#pragma endregion Register all the event sources in the event_queue

	al_set_mouse_z(0);

	//Start the timer
	al_start_timer(timer);
	gameTime = al_current_time();
	//GameObjectManager::GetInstance().Create();
	#pragma endregion All kinds of stuff get initialized here.

	AudioManager::GetInstance().PlaySong(0);

	#pragma region Game loop
	while(!GetDone())
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		#pragma region Get input

		#pragma region Keyboard input
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				GameObjectManager::GetInstance().SetPlaying(false);
				GameObjectManager::GetInstance().SetWon(false);
				GameObjectManager::GetInstance().SetLost(false);
				GameObjectManager::GetInstance().DestroyAllObjects();
				FileManager::GetInstance().LoadLevel(LVL_MENU);
				break;
			case ALLEGRO_KEY_UP:
				_keys[UP] = true;
				_keys_pressed[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys[DOWN] = true;
				_keys_pressed[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				_keys[LEFT] = true;
				_keys_pressed[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				_keys[RIGHT] = true;
				_keys_pressed[RIGHT] = true;
				break;
			case ALLEGRO_KEY_Q:
				_keys[Q_KEY]=true;
				_keys_pressed[Q_KEY] = true;
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = true;
				_keys_pressed[ALT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				_keys[ENTER] = true;
				_keys_pressed[ENTER] = true;
				if(_keys[ALT])
				{
					DisplayManager::GetInstance().ChangeState();
				}
				break;
				break;
			case ALLEGRO_KEY_M:
				AudioManager::GetInstance().ToggleMusic();
				break;
			case ALLEGRO_KEY_S:
				AudioManager::GetInstance().ToggleSoundFX();
				break;
			case ALLEGRO_KEY_LCTRL:
				GameObjectManager::GetInstance().DestroyAllObjects();
				FileManager::GetInstance().LoadLevel(LVL_2);
				GameObjectManager::GetInstance().Create();
				break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				break;
			case ALLEGRO_KEY_UP:
				_keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				_keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				_keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_Q:
				_keys[Q_KEY]=false;
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = false;
				break;
			}
		}
		#pragma endregion Get input from the keyboard
		#pragma region Mouse input
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			_mX=ev.mouse.x;
			_mY=ev.mouse.y;
			UpdateMouseCoordinates(_mX, _mY);
			_velZoom -= ev.mouse.z/200.0;
			al_set_mouse_z(0);
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)
			{
				_mouseButton[M_LEFT] = true;
				_mouseButtonPressed[M_LEFT] = true;
			}
			else if(ev.mouse.button & 2)
			{
				_mouseButton[M_RIGHT] = true;
				_mouseButtonPressed[M_RIGHT] = true;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if(ev.mouse.button & 1)
				_mouseButton[M_LEFT] = false;
			else if(ev.mouse.button & 2)
				_mouseButton[M_RIGHT] = false;
		}
		#pragma endregion Get input from the mouse
		#pragma region Other input
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ExitProgram();
		}
		#pragma endregion Other input

		#pragma endregion Get input from the user (via mouse, keyboard and display)
		#pragma region Timer
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			GameObjectManager::GetInstance().TimerEvent();
			AudioManager::GetInstance().Update();
			MoveCam();
			UpdateMouseCoordinates(_mX, _mY);
			//Reset variables
			for(int i=0; i<ENUM_KEYS_SIZE; i++)
				_keys_pressed[i]=false;
			_mouseButtonPressed[M_LEFT] = false;
			_mouseButtonPressed[M_RIGHT] = false;
		}
		#pragma endregion Timer event (for update and collision functions)
		#pragma region Draw
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			DisplayManager::GetInstance().Transform();
			/*
			//Blank the buffer
			al_set_target_bitmap(buffer);
			al_clear_to_color(al_map_rgb(0,0,0));

			//Blank the screen
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_clear_to_color(al_map_rgb(0,255,0));
			
			//Drawing stuff on the buffer
			al_set_target_bitmap(buffer);
			background.Draw();
			GameObjectManager::GetInstance().Draw();
			
			//Drawing the buffer on the screen
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			//al_draw_scaled_rotated_bitmap(buffer, _SCREEN_WIDTH/2.0,
			//	_SCREEN_HEIGHT/2.0, _SCREEN_WIDTH/2.0, _SCREEN_HEIGHT/2.0, 1/_zoom, 1/_zoom, 0, 0);
			al_draw_bitmap(buffer, 0,0,0);
			*/
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_clear_to_color(al_map_rgb(0,0,0));
			background.Draw();
			GameObjectManager::GetInstance().Draw();

			#pragma region borders
			//Add borders. It is so widescreen monitors won't show more content than square monitors.
			/*---NOT ZOOMABLE BORDERS---
			//left and right
			al_draw_filled_rectangle(-((_monitorWidth - _SCREEN_WIDTH*_scaleScreen)/2.0)+_camX-(_SCREEN_WIDTH/2.0),_camY-(_SCREEN_HEIGHT/2.0),_camX-(_SCREEN_WIDTH/2.0), _SCREEN_HEIGHT+_camY-(_SCREEN_HEIGHT/2.0), al_map_rgb(255,0,0));
			al_draw_filled_rectangle(_SCREEN_WIDTH+((_monitorWidth - _SCREEN_WIDTH*_scaleScreen)/2.0)+_camX-(_SCREEN_WIDTH/2.0),_camY-(_SCREEN_HEIGHT/2.0),_SCREEN_WIDTH+_camX-(_SCREEN_WIDTH/2.0), _camY+_SCREEN_HEIGHT-(_SCREEN_HEIGHT/2.0), al_map_rgb(255,0,0));

			
			//borders up and down
			al_draw_filled_rectangle(0,-(_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
				((float)_SCREEN_WIDTH*_scaleScreen),0 , al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, _SCREEN_HEIGHT + (_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
				((float)_SCREEN_WIDTH*_scaleScreen),  _SCREEN_HEIGHT, al_map_rgb(0,0,0));

			al_draw_filled_rectangle(_camX, -((_monitorHeight - _SCREEN_HEIGHT*_scaleScreen)/2.0)+_camY,_SCREEN_WIDTH+_camX, _camY, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(_camX, _SCREEN_HEIGHT + ((_monitorHeight - _SCREEN_HEIGHT*_scaleScreen)/2.0)+_camY,
				_SCREEN_WIDTH+_camX,_SCREEN_HEIGHT+_camY,al_map_rgb(0,0,0));
			*/


			//left
			//al_draw_filled_rectangle(-((_monitorWidth - _SCREEN_WIDTH*_scaleScreen)/2.0)+_camX-(_SCREEN_WIDTH/2.0*_zoom),
			//	_camY-(_LEVEL_HEIGHT/2.0*_zoom),_camX-(_SCREEN_WIDTH/2.0*_zoom), _LEVEL_HEIGHT+_camY-(_SCREEN_HEIGHT/2.0*_zoom), al_map_rgb(255,0,255));

			//al_draw_filled_rectangle(-((_monitorWidth - _LEVEL_WIDTH*_scaleScreen)/2.0)+_camX-(_LEVEL_WIDTH/2.0*_zoom),
			//	_camY-(_LEVEL_HEIGHT/2.0*_zoom),_camX-(_LEVEL_WIDTH/2.0*_zoom), _LEVEL_HEIGHT+_camY-(_LEVEL_HEIGHT/2.0*_zoom), al_map_rgb(255,0,255));
			//right
			//al_draw_filled_rectangle(_SCREEN_WIDTH+((_monitorWidth - _SCREEN_WIDTH*_scaleScreen)/2.0)+_camX-(_SCREEN_WIDTH/2.0*_zoom),_camY-(_SCREEN_HEIGHT/2.0*_zoom),
			//	_SCREEN_WIDTH+(_camX-(_SCREEN_WIDTH/2.0*_zoom)), _camY+_SCREEN_HEIGHT-(_SCREEN_HEIGHT/2.0*_zoom), al_map_rgb(255,0,255));

			//al_draw_filled_rectangle(_SCREEN_WIDTH+_camX-(_SCREEN_WIDTH/2.0*_zoom), _camY-(_SCREEN_HEIGHT/2.0*_zoom),
			//	_SCREEN_WIDTH+((_monitorWidth - _SCREEN_WIDTH*_scaleScreen)/2.0)+_camX-(_SCREEN_WIDTH/2.0*_zoom), _SCREEN_HEIGHT+_camY-(_SCREEN_HEIGHT/2.0*_zoom), al_map_rgb(255,0,255));
			
			//borders up and down
			//al_draw_filled_rectangle(0,-(_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
			//	((float)_SCREEN_WIDTH*_scaleScreen),0 , al_map_rgb(0,0,0));
			//al_draw_filled_rectangle(0, _SCREEN_HEIGHT + (_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
			//	((float)_SCREEN_WIDTH*_scaleScreen),  _SCREEN_HEIGHT, al_map_rgb(0,0,0));
				
			//al_draw_filled_rectangle(_camX, -((_monitorHeight - _SCREEN_HEIGHT*_scaleScreen)/2.0)+_camY,_SCREEN_WIDTH+_camX, _camY, al_map_rgb(0,0,0));
			//al_draw_filled_rectangle(_camX, _SCREEN_HEIGHT + ((_monitorHeight - _SCREEN_HEIGHT*_scaleScreen)/2.0)+_camY,
			//	_SCREEN_WIDTH+_camX,_SCREEN_HEIGHT+_camY,al_map_rgb(0,0,0));
			#pragma endregion

			//Show the actual display
			al_flip_display();
		}
		#pragma endregion Contains all the stuff that handles drawing everything on the screen

	}
	#pragma endregion This is the game loop, it will constantly be executed until the apllication is exited.

	#pragma region Cleaning
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	#pragma endregion Cleaning everything up

	return 0;
}

#pragma region functions

void MoveCam()
{
	if(_velZoom >= 0.001)
		_velZoom -=0.001;
	if(_velZoom <= -0.001)
		_velZoom +=0.001;
	if(_velZoom >-0.001 && _velZoom <0.001)
		_velZoom=0;
	if(_velZoom > 0.1)
		_velZoom = 0.1;
	if(_velZoom < -0.1)
		_velZoom = -0.1;
	
	_zoom+=_velZoom;

	if(_zoom < .1 )
	{
		_zoom=.1;
		_velZoom=0;
	}
	if(_SCREEN_WIDTH*_zoom>_LEVEL_WIDTH)
	{
		_zoom = _LEVEL_WIDTH/_SCREEN_WIDTH;
	}
	if(_SCREEN_HEIGHT*_zoom>_LEVEL_HEIGHT)
		_zoom = _LEVEL_HEIGHT/_SCREEN_HEIGHT;
	
	if(_camX < _SCREEN_WIDTH/2.0 * _zoom)
		_camX =  _SCREEN_WIDTH/2.0 * _zoom;
	else if(_camX > _LEVEL_WIDTH - (_SCREEN_WIDTH/2.0)*_zoom)
		_camX = _LEVEL_WIDTH - (_SCREEN_WIDTH/2.0)*_zoom;
	if(_camY < _SCREEN_HEIGHT/2.0 * _zoom)
		_camY = _SCREEN_HEIGHT/2.0 * _zoom;
	else if(_camY > _LEVEL_HEIGHT - (_SCREEN_HEIGHT/2.0)*_zoom)
		_camY = _LEVEL_HEIGHT - (_SCREEN_HEIGHT/2.0)*_zoom;
	
}

void UpdateMouseCoordinates(float mX, float mY)
{
	if(DisplayManager::GetInstance().GetState() == WINDOWED)
	{
		_mouseX = ((mX *_zoom) + _camX )- (_SCREEN_WIDTH/2.0*_zoom);
		_mouseY = ((mY *_zoom) + _camY) - (_SCREEN_HEIGHT/2.0*_zoom);				
	}
	else if(DisplayManager::GetInstance().GetState() == FULLSCREEN_WINDOW)
	{
		_mouseX = (((mX - ((_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0)) / _scaleScreen) *_zoom) + _camX - _SCREEN_WIDTH/2.0*_zoom;
		_mouseY = (((mY - ((_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0)) / _scaleScreen) *_zoom) + _camY - _SCREEN_HEIGHT/2.0*_zoom;				
	}
}

#pragma endregion All functions are in here (except for main())
//