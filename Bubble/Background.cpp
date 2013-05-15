#include "Background.h"
#include <allegro5/allegro_primitives.h>

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
	if(image!=NULL)
	{	
		int widthLeft=_LEVEL_WIDTH%imageWidth;
		int heightLeft=_LEVEL_HEIGHT%imageHeight;
		
		for(int j=0; j<_LEVEL_WIDTH+imageWidth; j+=imageWidth)
		{
			for(int i=0; i<_LEVEL_HEIGHT+imageHeight; i+=imageHeight)
			{
				if((_LEVEL_WIDTH-j)/imageWidth>0 && (_LEVEL_HEIGHT-i)/imageHeight>0)
					al_draw_bitmap_region(image, 0, 0, imageWidth, imageHeight, j, i,0);
				else if((_LEVEL_HEIGHT-i)/imageHeight>0)
					al_draw_bitmap_region(image, 0, 0, widthLeft, imageHeight, j, i, 0);
				else if((_LEVEL_WIDTH-j)/imageWidth>0)
					al_draw_bitmap_region(image, 0, 0, imageWidth, heightLeft, j, i, 0);
				else
					al_draw_bitmap_region(image, 0, 0, widthLeft, heightLeft, j, i, 0);
			}
		}
	}
}