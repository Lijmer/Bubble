#include "globals.h"

static int steps=0, seconds=0, minutes=0, hours=0;

int _LEVEL_WIDTH=0, _LEVEL_HEIGHT=0;

float _camX=0, _camY=0;
bool _keys[ENUM_KEYS_SIZE] = {false, false, false, false, false, false, false};
bool _keys_pressed[ENUM_KEYS_SIZE] = {false, false, false, false, false, false, false};

bool _mouseButton[2] = {false, false};
bool _mouseButtonPressed[2] = {false, false};
float _mouseX, _mouseY;
float _mX, _mY;

float _scaleScreen = -1;
float _startScaleScreen = -1;
float _monitorWidth = -1;
float _monitorHeight = -1;
float _velZoom = 0;
float _zoom = 1;
bool _zoomable=false;

int _saveNum=-1;

void UpdateTime()
{
	if(++steps>60)
	{
		steps=0;
		if(++seconds>60)
		{
			seconds=0;
			if(++minutes>60)
			{
				minutes=0;
				hours++;
			}
		}
	}
}

void SetTime(int hours, int minutes, int seconds, int steps)
{
	::hours = hours;
	::minutes = minutes;
	::seconds = seconds;
	::steps = steps;
}

void GetTime(int &hours, int &minutes, int &seconds, int &steps)
{
	hours = ::hours;
	minutes = ::minutes;
	seconds = ::seconds;
	steps = ::steps;
}