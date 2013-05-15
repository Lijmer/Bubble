#pragma once
#include "GameObject.h"
#include <vector>
class obj_AI_Bubble : public GameObject
{
public:
	obj_AI_Bubble(void);
	~obj_AI_Bubble(void);
	void Init(float x, float y, float velX, float velY, float volume);
	void Update();
	void Draw();
	void Collided(GameObject *other);

private:
	float destinationDirection;
	int shootCount;
	int removeBubbleFromShotBubblesCount;
	bool hasFoundDirection;

	//It stores the instance IDs
	std::vector<unsigned int> shotBubbles;

	float r,g,b;
	ALLEGRO_BITMAP *imageRed, *imageGreen;
};
