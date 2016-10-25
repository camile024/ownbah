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
#include "clientDebug.h"

#define UI_MAX_NODES 50 //PER PANEL
#define BTN_ACTIVE 0
#define BTN_DOWN 1
#define BTN_DISABLED 2

interface UI_Node;
class UI_Panel;
class UI_Button;




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
	std::string name = "";
public:
	virtual void draw(void) = 0;
	std::string getName() { return name; }
	float getX() { return posX; }
	float getY() { return posY; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	bool operator==(const UI_Node &node) const {
		return (this->posX == node.posX
			&& this->posY == node.posY
			&& this->width == node.width
			&& this->height == node.height
			&& this->name == node.name);
	}
	/*/friend class UI_Panel;
	UI_Node() = default;
	UI_Node(int x, int y, int x2, int y2) {
	posX = x; posY = y; width = x2; height = y2;
	parent = new UI_Node();
	}
	*/
};


/*
*=========================================
*	UI_Panel
*	Drawing GUI elements on it, keeping track of the nodes
*	Author: Kamil
*=========================================
*/
class UI_Panel : public UI_Node {
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
	void setColor(float, float, float, float);
	void setColorRGB(int, int, int, int);
	void addNode(UI_Node*);
	void removeNode(UI_Node*);
	void draw();
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
	void *action;
	UI_Panel *parent;
	byte state = BTN_ACTIVE;
	std::string name = "Button";
	struct {
		float r = 1.00f;
		float g = 1.00f;
		float b = 1.00f;
	} color;
public:
	void setState(byte);
	void onClick(void(*));
	void draw();
	void setColor(float, float, float);
	void setColorRGB(int, int, int);
	UI_Button(UI_Panel*, float, float, float, float, std::string);
};