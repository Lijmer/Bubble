#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
class obj_Menu_Button
{
public:
	obj_Menu_Button(void);
	~obj_Menu_Button(void);

	void Init(float x, float y, int kind);
	void Update();
	void UpdateClicked();
	void Draw();
	void Execute();

	static void NextButton();
	static void PreviousButton();
	static int GetSelectedButton() {return selectedButton;}

	static void SetNumButtons(int numButtons)			{obj_Menu_Button::numButtons=numButtons;}
	static void SetSelectedButton(int selectedButton)	{obj_Menu_Button::selectedButton = selectedButton;}

	void SetSelected(bool selected)		{obj_Menu_Button::selected = selected;}
	void SetAlive(bool alive)					{obj_Menu_Button::alive = alive;}

	bool GetAlive()			{return alive;}

	enum KIND
	{
		NEW_GAME,
		LOAD_GAME,
		OPTIONS,
		HELP,
		EXIT,
		MAIN_MENU,
		BACK=9,
		MUSIC_TOGGLE,
		MUSIC_VOLUME,
		SOUNDFX_TOGGLE,
		SOUNDFX_VOLUME,
		FULLSCREEN_TOGGLE,
		NEW_GAME1,
		NEW_GAME2,
		NEW_GAME3,
		LOAD_GAME1,
		LOAD_GAME2,
		LOAD_GAME3,
		NEXT_LEVEL,
		RETRY_LEVEL,
		RESUME
	};

private:
	static int selectedButton;
	static int numButtons;
	int buttonID;
	float x, y;
	int boundUp, boundDown, boundLeft, boundRight;
	int kind;
	bool selected;
	bool alive;

	ALLEGRO_BITMAP *image;

	void DrawTextOutlined(ALLEGRO_FONT *font, ALLEGRO_COLOR outlineColor, ALLEGRO_COLOR innerColor, float x, float y, int flags, char const *text);
};

