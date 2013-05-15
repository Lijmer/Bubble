#include "FontManager.h"
#include <allegro5/allegro_native_dialog.h>
#include "DisplayManager.h"


FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
}

FontManager& FontManager::GetInstance()
{
	static FontManager instance;
	return instance;
}

void FontManager::Init()
{
	al_init_font_addon();
	al_init_ttf_addon();
	nokiafc22_18_c = al_load_font("Fonts/nokiafc22.ttf",18, ALLEGRO_ALIGN_CENTER);
	if(nokiafc22_18_c==NULL)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(),"Error!", "FontManager", "Couldn't load nokiafc22 font", "ok sok", 0);
	}
}

ALLEGRO_FONT* FontManager::GetFont(char fontNum)
{
	if(fontNum==0)
	{
		return nokiafc22_18_c;
	}
	else
		return NULL;
}