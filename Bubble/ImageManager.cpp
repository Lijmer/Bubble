#include "ImageManager.h"

ImageManager::ImageManager(void)
{
}

ImageManager::~ImageManager(void)
{
	al_destroy_bitmap(img_player);
	al_destroy_bitmap(img_button);
	al_destroy_bitmap(img_bubble_red);
	al_destroy_bitmap(img_bubble_green);
	al_destroy_bitmap(bkg_space);
}

ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

void ImageManager::Init()
{
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	al_init_image_addon();
	img_player = al_load_bitmap("img/player/bubble.png");
	img_button = al_load_bitmap("img/button.png");
	img_bubble_red = al_load_bitmap("img/player/bubble_red.png");
	img_bubble_green = al_load_bitmap("img/player/bubble_green.png");

	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	bkg_space = al_load_bitmap("img/Background/space.jpg");

	std::string error = "";

	if(img_player == NULL)
		error = "img_player";
	else if(img_button == NULL)
		error = "img_button";
	else if(bkg_space == NULL)
		error = "bkg_space";
	else if(img_bubble_red==NULL)
		error = "img_bubble_red";
	else if(img_bubble_green == NULL)
		error = "img_bubble_green";

	if(error != "")
	{
		std::string finalError = "Couldn't load " + error + ".";
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", finalError.c_str(), "ok sok", 0);
	}
}


//This function returns an ALLEGRO_BITMAP based on the ID that is passed in.
ALLEGRO_BITMAP* ImageManager::GetImage(unsigned char ID)
{
	//if no value is passed in, it will show an error message
	if(ID == 255)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", 
			"ImageManager", "Not value or 255 has been passed in to GetImage(unsigned char ID)", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return NULL;
	}
	//Actually return the right image
	else if(ID == 0)
	{
		return img_player;
	}
	else if(ID == 1)
	{
		return img_bubble_red;
	}
	else if(ID == 2)
	{
		return img_bubble_green;
	}
	else if(ID == 99)
	{
		return img_button;
	}
	//if the ID is not in this function it will show an error message
	else
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager",
			"An unknown image ID was passed in to GetImage(unsigned char ID)", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return NULL;
	}
}

ALLEGRO_BITMAP* ImageManager::GetBackground(unsigned char ID)
{
	if(ID==255)
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ÏmageManager", 
			"No value or 255 has been passed in to GetBackgroud(unsigned char ID)", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return NULL;
	}
	else if(ID==0)
		return bkg_space;
	else
	{
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager",
			"An unknown background ID was passed in to GetBackground(unsigned char ID)", "ok sok", ALLEGRO_MESSAGEBOX_ERROR);
		return NULL;
	}
}