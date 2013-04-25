#pragma once

const short _SCREEN_WIDTH = 800;
const short _SCREEN_HEIGHT = 600;
const int _LEVEL_WIDTH = 800;
const int _LEVEL_HEIGHT = 600;
const float PI = 3.14159265f;

enum KEYS
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ALT
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
	PLAYER
};

extern float _camX, _camY;
extern bool _keys[5];
extern bool _mouseButton[2];
extern bool _mouseButtonPressed[2];
extern float _mouseX, _mouseY;

extern float _scaleScreen;
extern float _startScaleScreen;
extern float _monitorWidth;
extern float _monitorHeight;
extern float _velZoom;
extern float _zoom;
