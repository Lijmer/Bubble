#pragma once
#include "GameObject.h"
#include "obj_Bubble.h"
#include <allegro5/allegro_primitives.h>

class obj_Player : public GameObject
{
public:
	obj_Player();
	~obj_Player(void);

	void Init(float x, float y, float direction, float speed, float volume);
	void Update();
	void Draw();
	void Collided(GameObject *other);

private:

	//in radiants
	float mouseDir;

	float velX;
	float velY;

	//These are for calculating the direction from x,y to _mouseX, _mouseY
	//S = schuine zijde, O = overstaande zijde, A = aanliggende zijde (  van de driehoek ;)  )
	float S, O, A;
};
