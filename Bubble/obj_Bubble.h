#pragma once
#include "GameObject.h"
//#include "obj_Bubble.h"
#include <allegro5/allegro_primitives.h>
class obj_Bubble : public GameObject
{
public:
	obj_Bubble(void);
	~obj_Bubble(void);

	void Init(float x, float y, float velX, float velY, float volume);
	void Update();
	void Draw();
	void Collided(GameObject *other);

private:
	int r,g,b;
	ALLEGRO_BITMAP *imageRed, *imageGreen;
};

