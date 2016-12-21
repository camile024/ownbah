#pragma once
#include "gui.h"

#include "UI_Node.h"
#include "UI_Panel.h"
#include "gui_defines.h"
/*
*=========================================
*	UI_Label
*	Added to a specific UI_Panel
*	Stores text
*	Author: Kamil
*=========================================
*/
class UI_Label : public UI_Node {
	std::string caption;
	void* font;
	UI_Panel &parent;
	std::string name = "Button";
	struct {
		float r = 1.00f;
		float g = 1.00f;
		float b = 1.00f;
	} color;
public:
	void draw();
	void setColor(float, float, float);
	void setColorRGB(int, int, int);
	void setFont(void*);
	void setSizes(float, float);
	std::string getName(void) { return name; };
	UI_Panel& getParent() { return parent; }
	UI_Label(UI_Panel&, float, float, std::string);
};