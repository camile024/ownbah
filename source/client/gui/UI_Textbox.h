#pragma once
#include "gui.h"

#include "UI_Node.h"
#include "UI_Panel.h"
#include "gui_defines.h"
/*
*=========================================
*	UI_Textbox
*	Added to a specific UI_Panel
*	Stores the function to be called on click
*	Author: Kamil
*=========================================
*/
class UI_Textbox : public UI_Node {
	std::string text;
	void* font;
	UI_Panel &parent;
	byte state = BTN_ACTIVE;
	std::string name = "Textbox";
	bool selected;
	struct {
		float r = 1.00f;
		float g = 1.00f;
		float b = 1.00f;
	} color;
	int maxLength;
public:
	void setState(byte);
	byte getState();
	void draw();
	void setColor(float, float, float);
	void setColorRGB(int, int, int);
	void setFont(void*);
	void addChar(char);
	void setText(std::string);
	void select(void);
	void deselect(void);
	void removeChar(void);
	void setMaxLength(int l) { maxLength = l; };
	std::string getText(void);
	std::string getName(void) { return name; };
	UI_Panel& getParent() { return parent; }
	UI_Textbox(UI_Panel&, float, float, float, float);
};