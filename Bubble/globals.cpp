#include "globals.h"
float _camX=0, _camY=0;
bool _keys[ENUM_KEYS_SIZE] = {false, false, false, false, false, false};
bool _mouseButton[2] = {false, false};
bool _mouseButtonPressed[2] = {false, false};
float _mouseX, _mouseY;

float _scaleScreen = -1;
float _startScaleScreen = -1;
float _monitorWidth = -1;
float _monitorHeight = -1;
float _velZoom = 0;
float _zoom = 0;
