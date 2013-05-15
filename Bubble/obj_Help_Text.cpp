#include "obj_Help_Text.h"
#include "FontManager.h"

obj_Help_Text::obj_Help_Text(void)
{
}


obj_Help_Text::~obj_Help_Text(void)
{
}

void obj_Help_Text::Init(float x, float y)
{
	obj_Help_Text::x=x;
	obj_Help_Text::y=y;
}

void obj_Help_Text::Draw()
{
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+50,ALLEGRO_ALIGN_CENTER,
		"To start the game, go back to the main menu, then go to new game");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+70,ALLEGRO_ALIGN_CENTER,
		"and select a save file you want to save the game to. You can later");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+90,ALLEGRO_ALIGN_CENTER,
		"load the game by going to the load game menu.");


	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+120,ALLEGRO_ALIGN_CENTER,
		"You control the game with your mouse. In the game you are  a bubble");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+140,ALLEGRO_ALIGN_CENTER,
		"where you are trying to become the biggest of all the bubbles.");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+160,ALLEGRO_ALIGN_CENTER,
		"If you collide with a smaller bubble, you will absorb it. But");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+180,ALLEGRO_ALIGN_CENTER,
		"when you collide with a bigger bubble, you will be absorbed. You");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+200,ALLEGRO_ALIGN_CENTER,
		"can shoot a bit of yourself away to move by clicking.");

	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+230,ALLEGRO_ALIGN_CENTER,
		"Once you are the biggest bubble you win :D");
	DrawTextOutlined(FontManager::GetInstance().GetFont(0), al_map_rgb(0,0,0), al_map_rgb(255,255,255),x,y+250,ALLEGRO_ALIGN_CENTER,
		" If you get completly absorbed you lose :(");	
}

inline void obj_Help_Text::DrawTextOutlined(ALLEGRO_FONT *font, ALLEGRO_COLOR outlineColor, ALLEGRO_COLOR innerColor, float x, float y, int flags, char const *text)
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