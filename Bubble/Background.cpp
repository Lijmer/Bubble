#include "Background.h"


Background::Background(void)
{
	image = ImageManager::GetInstance().GetBackground(0);
	x=-1;
}


Background::~Background(void)
{
}

void Background::Draw()
{
	//if(++x>imageWidth)
	//{
		//x -= imageWidth;
	//}
	al_draw_bitmap(image, imageWidth - _camX, -_camY, ALLEGRO_FLIP_HORIZONTAL);
	al_draw_bitmap(image, - _camX, -_camY, 0);
}