#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "GameObject.h"
class obj_Help_Text : public GameObject
{
public:
	obj_Help_Text(void);
	~obj_Help_Text(void);
	void Init(float x, float y);
	void Draw();

private:
	void DrawTextOutlined(ALLEGRO_FONT *font, ALLEGRO_COLOR outlineColor, ALLEGRO_COLOR innerColor, float x, float y, int flags, char const *text);
};

