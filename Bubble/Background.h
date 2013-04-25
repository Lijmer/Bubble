#pragma once
#include "globals.h"
#include "ImageManager.h"
class Background
{
public:
	Background(void);
	~Background(void);
	void Draw();
private:
	ALLEGRO_BITMAP* image;
	float x;
	static const int imageWidth = 1920;
};

