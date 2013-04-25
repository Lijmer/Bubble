#pragma once
#include "GameObject.h"
#include "obj_Bubble.h"
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

};

