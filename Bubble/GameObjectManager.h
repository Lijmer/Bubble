#pragma once
#include <vector>
class GameObject;
class obj_Player;
class obj_Bubble;
class obj_AI_Bubble;

class GameObjectManager
{
public:
	GameObjectManager(void);
	~GameObjectManager(void);

	static GameObjectManager& GetInstance();

	void Create();
	void TimerEvent();
	void Draw();

	float GetPlayerVolume();

	GameObject* GetClosestBubble(float x, float y, unsigned int instanceID);
	GameObject* GetClosestBubble(float x, float y, unsigned int insatnceID, std::vector<GameObject*> &exceptions);

	obj_Bubble* CreateBubble(float x, float y, float velX, float velY, float volume);
	obj_AI_Bubble* CreateAIBubble(float x, float y, float velX, float velY, float volume);
private:
	void Update();
	void Collisions();
	void Cleaning();

	std::vector<GameObject *> objects;
	std::vector<GameObject *> pendingObjects;
	std::vector<GameObject *>::iterator objectsIter;
	std::vector<GameObject *>::iterator objectsIter2;
	std::vector<GameObject *>::iterator getClosestBubbleIter;
	std::vector<GameObject *>::iterator getClosestBubbleIter2;
	std::vector<GameObject *>::iterator pendingObjectsIter;

	obj_Player *obj_player;
	obj_Bubble *obj_bubble;
	obj_AI_Bubble *obj_ai_bubble;
};

