#include "obj_Menu_Button.h"
#include "globals.h"
#include "Exit.h"
#include "ImageManager.h"
#include "GameObjectManager.h"
#include "FileManager.h"
#include "FontManager.h"
#include "AudioManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>

int obj_Menu_Button::numButtons=0;
int obj_Menu_Button::selectedButton=1;

obj_Menu_Button::obj_Menu_Button(void)
{
	x=0;
	y=0;
	boundUp=32;
	boundDown=32;
	boundLeft=128;
	boundRight=128;
	image = ImageManager::GetInstance().GetImage(99);
	numButtons++;
	buttonID=numButtons;
	alive = true;
	selected=false;
}

obj_Menu_Button::~obj_Menu_Button(void)
{
}

void obj_Menu_Button::Init(float x, float y, int kind)
{
	obj_Menu_Button::x = x;
	obj_Menu_Button::y = y;
	obj_Menu_Button::kind = kind;
	
}

void obj_Menu_Button::Update()
{
	if(_mouseX > x-boundLeft && _mouseX < x+boundRight
		&& _mouseY > y-boundUp && _mouseY < y+boundDown)
	{
		while(selectedButton!=buttonID)
			NextButton();
		//if(_mouseButtonPressed[M_LEFT])
		//	Execute();
	}
}

void obj_Menu_Button::UpdateClicked()
{
	if(_mouseX > x-boundLeft && _mouseX < x+boundRight
		&& _mouseY > y-boundUp && _mouseY < y+boundDown
		&& _mouseButtonPressed[M_LEFT])
	{
		Execute();
	}
}

void obj_Menu_Button::Draw()
{
	//Draw the button
	if(!selected)
		al_draw_bitmap_region(image,0,0,256,64,x-128,y-32,0);
	else 
		al_draw_bitmap_region(image,0,64,256,64,x-128,y-32,0);

	//Draw the text on the button
	if(kind==NEW_GAME)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"New Game");
	}
	else if(kind==LOAD_GAME)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Load Game");
	}
	else if(kind == OPTIONS)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Options");
	}
	else if(kind == HELP)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Help");
	}
	else if(kind == EXIT)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Exit");
	}
	else if(kind == MAIN_MENU)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Main Menu");
	}
	else if(kind == BACK)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
			al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Back");
	}
	else if(kind == MUSIC_TOGGLE)
	{
		if(AudioManager::GetInstance().GetMusicEnabled())
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Music: On");
		else
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Music: Off");
	}
	else if(kind == MUSIC_VOLUME)
	{
		std::stringstream ss;
		ss << "Music Volume: " << int(AudioManager::GetInstance().GetMusicVolume()*100);
		std::string text = ss.str();
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,text.c_str());
	}
	else if(kind == SOUNDFX_TOGGLE)
	{
		if(AudioManager::GetInstance().GetSoundFXEnabled())
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Sound Effects: On");
		else
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"SoundEffects: Off");
	}
	else if(kind == SOUNDFX_VOLUME)
	{
		std::stringstream ss;
		ss << "Sound FX Volume: " << int(AudioManager::GetInstance().GetSoundFXVolume()*100);
		std::string text = ss.str();
		DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,text.c_str());
	}
	else if(kind == FULLSCREEN_TOGGLE)
	{
		if(DisplayManager::GetInstance().GetState() == FULLSCREEN_WINDOW)
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Full Screen: On");
		else
			DrawTextOutlined(FontManager::GetInstance().GetFont(0),
				al_map_rgb(0,0,0), al_map_rgb(255,255,255), x, y-10,1,"Full Screen: Off");
	}
	else if(kind == NEW_GAME1)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "New Game 1");
	}
	else if(kind == NEW_GAME2)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "New Game 2");
	}
	else if(kind == NEW_GAME3)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "New Game 3");
	}
	else if(kind == LOAD_GAME1)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Load Game 1");
	}
	else if(kind == LOAD_GAME2)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Load Game 2");
	}
	else if(kind == LOAD_GAME3)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Load Game 3");
	}
	else if(kind == NEXT_LEVEL)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Next Level");
	}
	else if(kind == RETRY_LEVEL)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Retry Level");
	}
	else if(kind == RESUME)
	{
		DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0),
			al_map_rgb(255,255,255), x, y-10, 1, "Resume");
	}
}

void obj_Menu_Button::Execute()
{
	AudioManager::GetInstance().PlaySoundEffect(0);
	if(kind == NEW_GAME)
	{		
		GameObjectManager::GetInstance().DestroyAllObjects();
		GameObjectManager::GetInstance().CreateButton(400,100,NEW_GAME1);
		GameObjectManager::GetInstance().CreateButton(400,200,NEW_GAME2);
		GameObjectManager::GetInstance().CreateButton(400,300,NEW_GAME3);
		GameObjectManager::GetInstance().CreateButton(400,500,BACK);
	}
	else if(kind == LOAD_GAME)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		GameObjectManager::GetInstance().CreateButton(400,100,LOAD_GAME1);
		GameObjectManager::GetInstance().CreateButton(400,200,LOAD_GAME2);
		GameObjectManager::GetInstance().CreateButton(400,300,LOAD_GAME3);
		GameObjectManager::GetInstance().CreateButton(400,500,BACK);
	}
	else if(kind == OPTIONS)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().LoadLevel(LVL_OPTIONS);
		GameObjectManager::GetInstance().CreateButton(200,100,MUSIC_TOGGLE);
		GameObjectManager::GetInstance().CreateButton(600,100,MUSIC_VOLUME);
		GameObjectManager::GetInstance().CreateButton(200,200,SOUNDFX_TOGGLE);
		GameObjectManager::GetInstance().CreateButton(600,200,SOUNDFX_VOLUME);
		GameObjectManager::GetInstance().CreateButton(400,300,FULLSCREEN_TOGGLE);
	}
	else if(kind == HELP)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().LoadLevel(LVL_HELP);
		GameObjectManager::GetInstance().CreateHelpTextObject(400,0);
	}
	else if(kind == EXIT)
	{
		ExitProgram();
	}
	else if(kind == MAIN_MENU)
	{
		GameObjectManager::GetInstance().SetPlaying(false);
		GameObjectManager::GetInstance().SetWon(false);
		GameObjectManager::GetInstance().SetLost(false);
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().LoadLevel(LVL_MENU);
	}
	else if(kind == BACK)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().LoadLevel(LVL_MENU);
	}
	else if(kind == MUSIC_TOGGLE)
	{
		AudioManager::GetInstance().ToggleMusic();
	}
	else if(kind == MUSIC_VOLUME)
	{
		AudioManager::GetInstance().ChangeMusicVolume();
	}
	else if(kind == SOUNDFX_TOGGLE)
	{
		AudioManager::GetInstance().ToggleSoundFX();
	}
	else if(kind == SOUNDFX_VOLUME)
	{
		AudioManager::GetInstance().ChangeSoundFXVolume();
	}
	else if(kind == FULLSCREEN_TOGGLE)
	{
		DisplayManager::GetInstance().ChangeState();
	}
	else if(kind == NEW_GAME1)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().SetCurrentLevel(LVL_1);
		FileManager::GetInstance().LoadLevel(LVL_1);
		FileManager::GetInstance().SetSaveNum(1);
		_saveNum=1;
	}
	else if(kind == NEW_GAME2)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().SetCurrentLevel(LVL_1);
		FileManager::GetInstance().LoadLevel(LVL_1);
		GameObjectManager::GetInstance().Create();
		FileManager::GetInstance().SetSaveNum(2);
		_saveNum = 2;
	}
	else if(kind == NEW_GAME3)
	{
		GameObjectManager::GetInstance().DestroyAllObjects();
		FileManager::GetInstance().SetCurrentLevel(LVL_1);
		FileManager::GetInstance().LoadLevel(LVL_1);
		GameObjectManager::GetInstance().Create();
		FileManager::GetInstance().SetSaveNum(3);
		_saveNum = 3;
	}
	else if(kind == LOAD_GAME1)
	{
		FileManager::GetInstance().SetSaveNum(1);
		FileManager::GetInstance().Load();
		_saveNum = 1;
	}
	else if(kind == LOAD_GAME2)
	{
		FileManager::GetInstance().SetSaveNum(2);
		FileManager::GetInstance().Load();
		_saveNum = 2;
	}
	else if(kind == LOAD_GAME3)
	{
		FileManager::GetInstance().SetSaveNum(3);
		FileManager::GetInstance().Load();
		_saveNum = 3;
	}
	else if(kind == NEXT_LEVEL)
	{
		FileManager::GetInstance().AdvanceLevel();
		FileManager::GetInstance().Save();
		FileManager::GetInstance().Load();
	}
	else if(kind == RETRY_LEVEL)
	{
		FileManager::GetInstance().Load();
	}
	else if(kind == RESUME)
	{
		GameObjectManager::GetInstance().Pause();
	}
	else
	{
		//Give error and exit
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "obj_Menu_Button", "Unknown kind", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
	}
}

//Static functions
void obj_Menu_Button::NextButton()
{
	selectedButton++;
	if(selectedButton>numButtons)
	{
		selectedButton=1;
	}
}

void obj_Menu_Button::PreviousButton()
{
	if(--selectedButton<1)
	{
		selectedButton=numButtons;
	}
}

//Private functions
inline void obj_Menu_Button::DrawTextOutlined(ALLEGRO_FONT *font, ALLEGRO_COLOR outlineColor, ALLEGRO_COLOR innerColor, float x, float y, int flags, char const *text)
{
	//outline
	al_draw_text(font, outlineColor,x-1,y-1,flags,text);
	al_draw_text(font, outlineColor,x,y-1,flags,text);
	al_draw_text(font, outlineColor,x+1,y-1,flags,text);
	al_draw_text(font, outlineColor,x-1,y,flags,text);
	al_draw_text(font, outlineColor,x,y,flags,text);
	al_draw_text(font, outlineColor,x+1,y,flags,text);
	al_draw_text(font, outlineColor,x-1,y+1,flags,text);
	al_draw_text(font, outlineColor,x,y+1,flags,text);
	al_draw_text(font, outlineColor,x+1,y+1,flags,text);
	//inner
	al_draw_text(font, innerColor,x,y,flags,text);
}