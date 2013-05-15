#pragma once

const short _SCREEN_WIDTH = 800;
const short _SCREEN_HEIGHT = 600;
extern int _LEVEL_WIDTH;
extern int _LEVEL_HEIGHT;
const float PI = 3.14159265f;

enum KEYS
{
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	Q_KEY,
	ALT,
	ENTER,
	ENUM_KEYS_SIZE
};
enum MOUSE
{
	M_LEFT=0,
	M_RIGHT
};

enum DISPLAY_STATE
{
	WINDOWED,
	FULLSCREEN_WINDOW
};

enum OBJECT_ID
{
	UNDEFINED = -1,
	PLAYER,
	BUBBLE,
	AI_BUBBLE
};

enum LVL
{
	LVL_MENU,
	LVL_NEW_GAME,
	LVL_LOAD_GAME,
	LVL_OPTIONS,
	LVL_HELP,
	LVL_1=10,
	LVL_2,
	LVL_3,
	LVL_4
};

extern float _camX, _camY;
extern bool _keys[ENUM_KEYS_SIZE];
extern bool _keys_pressed[ENUM_KEYS_SIZE];
extern bool _mouseButton[2];
extern bool _mouseButtonPressed[2];
extern float _mouseX, _mouseY;
extern float _mX, _mY;

extern float _scaleScreen;
extern float _startScaleScreen;
extern float _monitorWidth;
extern float _monitorHeight;
extern float _velZoom;
extern float _zoom;
extern bool _zoomable; 

extern int _saveNum;

extern void UpdateTime();
extern void SetTime(int hours, int minutes, int seconds, int steps);
extern void GetTime(int &hours, int &minutes, int &seconds, int &steps);