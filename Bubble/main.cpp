#pragma region includes
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

#include "DisplayManager.h"
#include "ImageManager.h"

#include "GameObject.h"

#include "obj_Player.h"
#include "obj_Bubble.h"

#include <iostream>

#pragma endregion

#pragma region variables
std::vector<GameObject *> objects;
std::vector<GameObject *> pendingObjects;
std::vector<GameObject *>::iterator objectsIter;
std::vector<GameObject *>::iterator objectsIter2;
std::vector<GameObject *>::iterator pendingObjectsIter;

obj_Player *obj_player = NULL;
obj_Bubble *obj_bubble = NULL;
#pragma endregion This contains variables that are used by all kinds of functions in this file

#pragma region Prototypes
void MoveCam();
obj_Bubble* __cdecl CreateBubble(float x, float y, float velX, float velY, float volume);
#pragma endregion Contains declerations of functions later in this file

#pragma region main variables
ALLEGRO_EVENT_QUEUE *event_queue	= NULL;
ALLEGRO_TIMER *timer				= NULL;
ALLEGRO_TRANSFORM camera;
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
	
	#pragma region Create objects
	//Create Object This method of creating objects is temporary and this code will be changed soon!!
	obj_player = new obj_Player(&CreateBubble);
	obj_player->Init(_SCREEN_WIDTH/2, _SCREEN_HEIGHT/2, 0, 0, 104); 
	objects.push_back(obj_player);

	obj_bubble = new obj_Bubble();
	obj_bubble->Init(0,0,0,0,10);
	objects.push_back(obj_bubble);
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
	
	#pragma endregion All kinds of stuff get initialized here.

	#pragma region Game loop
	while(!done)
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
				break;
			case ALLEGRO_KEY_UP:
				_keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				_keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				_keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				_keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				if(_keys[ALT])
				{
					DisplayManager::GetInstance().ChangeState();
				}
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
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
			case ALLEGRO_KEY_ALT:
				_keys[ALT] = false;
				break;
			}
		}
		#pragma endregion Get input from the keyboard

		#pragma region Mouse input
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			if(DisplayManager::GetInstance().GetState() == WINDOWED)
			{
				_mouseX = (ev.mouse.x + ((_SCREEN_WIDTH * (1/_zoom) - _SCREEN_WIDTH)/2.0)) / (1/_zoom);
				_mouseY = (ev.mouse.y+ ((_SCREEN_HEIGHT * (1/_zoom) - _SCREEN_HEIGHT)/2.0)) / (1/_zoom);
			}
			else if(DisplayManager::GetInstance().GetState() == FULLSCREEN_WINDOW)
			{
				
				_mouseX = (((ev.mouse.x - ((_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0)) / _scaleScreen) + ((_SCREEN_WIDTH * (1/_zoom) - _SCREEN_WIDTH)/2.0)) / (1/_zoom);
				_mouseY = (((ev.mouse.y - ((_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0)) / _scaleScreen) + ((_SCREEN_HEIGHT * (1/_zoom) - _SCREEN_HEIGHT)/2.0)) / (1/_zoom);
				
				//_mouseX = ((ev.mouse.x + ((_SCREEN_WIDTH * (1/_zoom) -_SCREEN_WIDTH /2.0)) / (1/_zoom)) - ((_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0)) / _scaleScreen;
				//_mouseX = (ev.mouse.x + /*((_SCREEN_WIDTH * (1/_zoom) -_SCREEN_WIDTH /2.0))*/ - ((_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0)) / (1/_zoom) / _scaleScreen;
				//_mouseY = ev.mouse.y /_scaleScreen;
				
			}
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
			done=true;
		}
		#pragma endregion

		#pragma endregion Get input from the user (via mouse, keyboard and display);

		#pragma region Update
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;


			for(objectsIter = objects.begin(); objectsIter!= objects.end(); objectsIter++)
			{
				(*objectsIter)->Update();
			}

			//This pushes all objects that were created in the update event to the objects vector
			for(pendingObjectsIter = pendingObjects.begin(); pendingObjectsIter!=pendingObjects.end(); )
			{
				objects.push_back(*pendingObjectsIter);
				pendingObjectsIter = pendingObjects.erase(pendingObjectsIter);
			}

			for(objectsIter = objects.begin(); objectsIter!=objects.end(); objectsIter++)
			{
				for(objectsIter2=objectsIter; objectsIter2!=objects.end(); objectsIter2++)
				{
					if(((*objectsIter)->GetInstanceID() == (*objectsIter2)->GetInstanceID()))
						continue;
					if((*objectsIter)->CheckCollision(*objectsIter2))
					{
						(*objectsIter)->Collided(*objectsIter2);
						(*objectsIter2)->Collided(*objectsIter);
					}
				}
			}

			//Delete all objects where alive==false
			for(objectsIter = objects.begin(); objectsIter!=objects.end();)
			{
				if(!(*objectsIter)->getAlive())
				{
					delete (*objectsIter);
					objectsIter = objects.erase(objectsIter);
				}
				else
					objectsIter++;
			}

			MoveCam();

			//Reset variables
			_mouseButtonPressed[M_LEFT] = false;
			_mouseButtonPressed[M_RIGHT] = false;

		}
		#pragma endregion Timer event (for update and collision functions)

		#pragma region Draw
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			//Blank the buffer
			al_set_target_bitmap(buffer);
			al_clear_to_color(al_map_rgb(0,0,0));
			//Blank the screen
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_clear_to_color(al_map_rgb(0,255,0));
			
			//Drawing stuff on the buffer
			al_set_target_bitmap(buffer);
			//al_draw_filled_rectangle(100-_camX, 100-_camY, _SCREEN_WIDTH-100-_camX, _SCREEN_HEIGHT-100-_camY, al_map_rgb(255,0,255));
			
			al_draw_filled_rectangle(0-_camX, 0-_camY, 32-_camX, 32-_camY, al_map_rgb(255,0,255));
			al_draw_filled_rectangle(_LEVEL_WIDTH - 32 - _camX, 0 -_camY, _LEVEL_WIDTH -_camX, 32 -_camY, al_map_rgb(255,0,255));
			al_draw_filled_rectangle(_LEVEL_WIDTH - 32- _camX, _LEVEL_HEIGHT - 32-_camY, _LEVEL_WIDTH - _camX, _LEVEL_HEIGHT-_camY, al_map_rgb(255,0,255));
			al_draw_filled_rectangle(0 - _camX, _LEVEL_HEIGHT-32-_camY, 32 - _camX, _LEVEL_HEIGHT-_camY, al_map_rgb(255,0,255));
			al_draw_line(_LEVEL_WIDTH/2.0 -_camX, -_camY, _LEVEL_WIDTH/2.0 -_camX, _LEVEL_HEIGHT-_camY, al_map_rgb(0,0,255), 2);
			al_draw_line(-_camX, _LEVEL_HEIGHT/2.0 -_camY, _LEVEL_WIDTH - _camX, _LEVEL_HEIGHT/2.0 -_camY, al_map_rgb(0,0,255), 2);

			for(objectsIter=objects.begin(); objectsIter!=objects.end(); objectsIter++)
			{
				(*objectsIter)->Draw();
			}
			
			//Drawing the buffer on the screen
			al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
			al_draw_scaled_rotated_bitmap(buffer, _SCREEN_WIDTH/2.0,
				_SCREEN_HEIGHT/2.0, _SCREEN_WIDTH/2.0, _SCREEN_HEIGHT/2.0, 1/_zoom, 1/_zoom, 0, 0);

			#pragma region borders
			//Add borders. It is so widescreen monitors won't show more content than square monitors.
			//left and right
			al_draw_filled_rectangle((-_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0, 
				(_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0,0, _SCREEN_HEIGHT, al_map_rgb(0,0,0));
			al_draw_filled_rectangle(_SCREEN_WIDTH+(_monitorWidth - ((float)_SCREEN_WIDTH*_scaleScreen))/2.0, 
				(_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, _SCREEN_WIDTH, _SCREEN_HEIGHT, al_map_rgb(0,0,0));
			//borders up and down
			al_draw_filled_rectangle(0,-(_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
				((float)_SCREEN_WIDTH*_scaleScreen),0 , al_map_rgb(0,0,0));
			al_draw_filled_rectangle(0, _SCREEN_HEIGHT + (_monitorHeight - ((float)_SCREEN_HEIGHT*_scaleScreen))/2.0, 
				((float)_SCREEN_WIDTH*_scaleScreen),  _SCREEN_HEIGHT, al_map_rgb(0,0,0));
			#pragma endregion

			//Show the actual display
			al_flip_display();
		}
		#pragma endregion Contains all the stuff that handles drawing everything on the screen
	}
	#pragma endregion This is the game loop, it will constantly be executed until the apllication is exited.

	#pragma region Cleaning

	for(objectsIter = objects.begin(); objectsIter!=objects.end(); )
	{
		delete (*objectsIter);
		objectsIter = objects.erase(objectsIter);
	}

	DisplayManager::GetInstance().Clean();
	ImageManager::GetInstance().Clean();

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	#pragma endregion Cleaning everything up

	return 0;
}

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
	if(_zoom > 1)
	{
		_zoom=1;
		_velZoom=0;
	}
}

obj_Bubble* __cdecl CreateBubble(float x, float y, float velX, float velY, float volume)
{
	obj_bubble = new obj_Bubble();
	obj_bubble->Init(x,y,velX,velY,volume);
	pendingObjects.push_back(obj_bubble);
	return obj_bubble;
}
