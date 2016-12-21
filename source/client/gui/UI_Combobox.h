#pragma once
//standard includes
#include "gui.h"

#include "UI_Node.h"
#include "UI_Panel.h"
#include "gui_defines.h"
/*
*=========================================
*	UI_Combobox
*	Added to a specific UI_Panel
*	Can be opened and certain values can be selected
*	Author: Kamil
*=========================================
*/

class UI_Combobox : public UI_Node {
	std::string caption;
	std::vector<std::string*> items;
	void* font;
	void(*action)(void);
	int selected = -1;
	UI_Panel &parent;
	byte state = BTN_ACTIVE;
	std::string name = "Combobox";
	int start = 0;
	int end = 0;
public:
	void setState(byte s) { state = s; }
	byte getState() { return state; }
	void onClick(int, int);
	void setAction(void(*f)()) { action = f; };
	void setFont(void*);
	void draw();
	void addItem(std::string*);
	void removeItem(std::string*);
	UI_Panel& getParent() { return parent; }
	UI_Combobox(UI_Panel&, float, float, float, float, std::string);
	int getSelectedIndex() { return selected; }
	std::string getSelected(int i) { return *items[i]; }
};