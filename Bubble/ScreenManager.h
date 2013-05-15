#pragma once
class ScreenManager
{
public:
	ScreenManager(void);
	~ScreenManager(void);

	enum STATE
	{
		MENU,
		GAME
	};
	enum LEVEL
	{
		LVL_LEVEL1
	};



	int GetState()		{return state;}
	int GetLevel()		{return level;}

	static ScreenManager& GetInstance();


	void ChangeLevel(int levelNum);	
	void ChangeState(int state);

private:
	int state;
	int level;
};

