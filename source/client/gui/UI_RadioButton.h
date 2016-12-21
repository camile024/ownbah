#pragma once

#include <math.h>

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

class UI_RadioButton : public UI_Node {
	std::string caption;
	void* font;
	void(*action)(void);
	bool checked = false;
	UI_Panel &parent;
	byte state = BTN_ACTIVE;
	std::string name = "RadioButton";
	struct {
		float r = 1.00f;
		float g = 1.00f;
		float b = 1.00f;
	} color;
public:
	int group;
	void setState(byte);
	byte getState();
	void onClick();
	void setAction(void(*)());
	void setFont(void*);
	void draw();
	std::string getName(void) { return name; };
	UI_Panel& getParent() { return parent; };
	UI_RadioButton(UI_Panel&, float, float, float, float, std::string);
	void check();
	void unCheck();
};