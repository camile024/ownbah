#pragma once
#include "gui.h"

#include "UI_Node.h"
#include "UI_Panel.h"

/*
*=========================================
*	UI_Checkbox
*	Added to a specific UI_Panel
*	Can be checked/unchecked
*	Author: Kamil
*=========================================
*/

class UI_Checkbox : public UI_Node {
	std::string caption;
	void(*action)(void);
	bool checked = false;
	UI_Panel &parent;
	byte state = BTN_ACTIVE;
	std::string name = "Checkbox";
public:
	void setState(byte);
	byte getState();
	void onClick();
	void setAction(void(*)());
	void draw();
	UI_Panel& getParent() { return parent; }
	UI_Checkbox(UI_Panel&, float, float, float, float, std::string);
	void toggle();
};