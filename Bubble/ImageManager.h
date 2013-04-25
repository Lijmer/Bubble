#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <string>

#include "DisplayManager.h"
class ImageManager
{
public:
	ImageManager(void);
	~ImageManager(void);

	static ImageManager& GetInstance();

	void Init();

	void Clean();

	ALLEGRO_BITMAP* GetImage(unsigned char ID = 255);

private:
	ALLEGRO_BITMAP *img_player;
};
