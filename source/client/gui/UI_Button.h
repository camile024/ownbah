#pragma once

#include "gui.h"

#include "UI_Node.h"
#include "UI_Panel.h"
#include "gui_defines.h"
/*
*=========================================
*	UI_Button
*	Added to a specific UI_Panel
*	Stores the function to be called on click
*	Author: Kamil
*=========================================
*/
class UI_Button : public UI_Node {
	std::string caption;
	void* font;
	void(*action)(void);
	UI_Panel &parent;
	byte state = BTN_ACTIVE;
	std::string name = "Button";
	struct {
		float r = 1.00f;
		float g = 1.00f;
		float b = 1.00f;
	} color;
public:
	void setState(byte);
	byte getState();
	void onClick();
	void setAction(void(*)());
	void draw();
	void setColor(float, float, float);
	void setColorRGB(int, int, int);
	void setFont(void*);
	std::string getName(void) { return name; };
	UI_Panel& getParent() { return parent; }
	UI_Button(UI_Panel&, float, float, float, float, std::string);
};