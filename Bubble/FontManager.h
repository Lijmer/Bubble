#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class FontManager
{
public:
	FontManager(void);
	~FontManager(void);
	static FontManager& GetInstance();

	void Init();

	ALLEGRO_FONT* GetFont(char fontNum);

private:
	ALLEGRO_FONT* nokiafc22_18_c;
};
