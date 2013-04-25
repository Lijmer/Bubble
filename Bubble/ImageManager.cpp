#include "ImageManager.h"

ImageManager::ImageManager(void)
{
}


ImageManager::~ImageManager(void)
{
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


	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	bkg_space = al_load_bitmap("img/Background/space.jpg");

	std::string error = "";

	if(img_player == NULL)
		error = "img_player";
	else if(bkg_space == NULL)
		error = "bkg_space";

	if(error != "")
	{
		std::string finalError = "Couldn't load " + error + ".";
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", finalError.c_str(), "ok sok", 0);
	}
}


void ImageManager::Clean()
{
	al_destroy_bitmap(img_player);
};


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
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "�mageManager", 
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