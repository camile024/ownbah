#pragma once
//standard includes
#include "gui.h"

#include "UI_Panel.h"
#include "gui_defines.h"


/*
*=========================================
*	General node for GUI
*	Author: Kamil
*=========================================
*/
class UI_Panel;
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
	virtual std::string getName() { return name; }
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

/* WithinCoords function for use in mouse handling functions */
bool withinCoords(int x, int y, UI_Node* a);