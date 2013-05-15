#pragma once
#include <vector>
class GameObject;
class obj_Player;
class obj_Bubble;
class obj_AI_Bubble;
class obj_Menu_Button;
class obj_Help_Text;

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
	GameObject* GetClosestBubble(float x, float y, unsigned int insatnceID, std::vector<unsigned int> &exceptions);
	void CreateButton(float x, float y, int kind);
	void CreateHelpTextObject(float x, float y);

	
	obj_Bubble* CreateBubble(float x, float y, float velX, float velY, float volume);
	obj_AI_Bubble* CreateAIBubble(float x, float y, float velX, float velY, float volume);

	void DestroyAllObjects();
	void DestroyAllButtons();
	

	void Pause();


	float TimesBiggerThanPlayer(float volume);

	bool CheckWinningCondition();
	bool CheckLosingCondition();

	void SetPlaying(bool playing)	{GameObjectManager::playing = playing;}
	void SetWon(bool won)			{GameObjectManager::won = won;}
	void SetLost(bool lost)			{GameObjectManager::lost = lost;}
	bool IsPlaying()				{return playing;}
	bool GetWon()					{return won;}
private:
	void Update();
	void UpdateButtons();
	void Collisions();
	void Cleaning();
	
	bool won, lost, playing, paused;

	std::vector<GameObject *> objects;
	std::vector<GameObject *> pendingObjects;
	std::vector<GameObject *>::iterator objectsIter;
	std::vector<GameObject *>::iterator objectsIter2;
	std::vector<GameObject *>::iterator getClosestBubbleIter;
	std::vector<GameObject *>::iterator pendingObjectsIter;

	std::vector<obj_Menu_Button*> buttons;

	std::vector<void *> other;

	std::vector<unsigned int>::iterator uintIter;

	obj_Player *obj_player;
	obj_Bubble *obj_bubble;
	obj_AI_Bubble *obj_ai_bubble;
	obj_Menu_Button* obj_menu_button;
	obj_Help_Text* obj_help_text;
};

