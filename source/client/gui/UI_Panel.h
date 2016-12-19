#pragma once
//standard includes
#include "gui.h"

#include "UI_Node.h"
#include "gui_defines.h"
/*
*=========================================
*	UI_Panel
*	Drawing GUI elements on it, keeping track of the nodes
*	Author: Kamil
*=========================================
*/
interface UI_Node;
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