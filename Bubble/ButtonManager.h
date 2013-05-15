#pragma once
#include <vector>
class obj_Menu_Button;
class ButtonManager
{
public:
	ButtonManager(void);
	~ButtonManager(void);

	obj_Menu_Button* CreateButton(float x, float y, int kind);

private:
	obj_Menu_Button *obj_menu_button;

	int selectedButton;

	std::vector<obj_Menu_Button *> buttons;

};
