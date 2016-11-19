#pragma once
//standard includes
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <vector>

//graphics
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GL\glut.h>

//custom headers
#include "../clientDebug.h"

#define UI_MAX_NODES 50 //PER PANEL
#define BTN_ACTIVE 0
#define BTN_DOWN 1
#define BTN_DISABLED 2
#define BTN_HOVER 3

#define COMBO_ACTIVE 0
#define COMBO_OPEN 1
#define COMBO_HOVER 4

interface UI_Node;
class UI_Panel;
class UI_Button;



bool reshapeWindow(int, int, int, int, int, int);

/*
*=========================================
*	General node for GUI
*	Author: Kamil
*=========================================
*/
interface UI_Node {
protected:
	float posX;
	float posY;
	float width;
	float height;
	//UI_Panel& parent;
	std::string name = "";
public:
	virtual void draw(void) = 0;
	std::string getName() { return name; }
	float getX() { return posX; }
	float getY() { return posY; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	virtual UI_Panel& getParent(void) = 0;
	bool operator==(const UI_Node &node) const {
		return (this->posX == node.posX
			&& this->posY == node.posY
			&& this->width == node.width
			&& this->height == node.height
			&& this->name == node.name);
	}
	void setSizes(float x, float y, float width, float height);
};


/*
*=========================================
*	UI_Panel
*	Drawing GUI elements on it, keeping track of the nodes
*	Author: Kamil
*=========================================
*/
class UI_Panel {
protected:
	float posX;
	float posY;
	float width;
	float height;
	std::vector<UI_Node*> nodes;
	std::string name = "Panel";
	struct {
		float r = 1;
		float g = 1;
		float b = 1;
		float a = 0.75;
	} color;
public:
	UI_Panel(float, float, float, float);
	std::string getName() { return name; }
	float getX() { return posX; }
	float getY() { return posY; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	void setColor(float, float, float, float);
	void setColorRGB(int, int, int, int);
	void addNode(UI_Node&);
	void removeNode(UI_Node&);
	void draw();
	void setSizes(float x, float y, float width, float height);
	std::vector<UI_Node*>& getNodes();
};

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
	void (*action)(void);
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
	void setAction(void (*)());
	void draw();
	void setColor(float, float, float);
	void setColorRGB(int, int, int);
	UI_Panel& getParent() { return parent; }
	UI_Button(UI_Panel&, float, float, float, float, std::string);
};

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
	void draw();
	void addItem(std::string*);
	void removeItem(std::string*);
	UI_Panel& getParent() { return parent; }
	UI_Combobox(UI_Panel&, float, float, float, float, std::string);
	int getSelectedIndex() { return selected; }
	std::string getSelected(int i) { return *items[i]; }
};