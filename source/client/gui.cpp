/*
*	BASE GUI ELEMENTS
*
*	Needs cleaning up and moving the class
*	definitions to gui.h
*
*	Author: Kamil
*/

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
#include "gui.h"

#define UI_MAX_NODES 50 //PER PANEL

/*
*=========================================
*	General node for GUI
*	Author: Kamil
*=========================================
*/
interface UI_Node {
protected:
	int posX;
	int posY;
	int width;
	int height;
	std::string name = "";
public:
	void draw();
	std::string getName() { return name; }
	int getX() { return posX; }
	int getY() { return posY; }
	int getWidth() { return width; }
	int getHeight() { return height; }
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
	std::vector<UI_Node> nodes;
	std::string name = "Panel";
public:
	UI_Panel(int, int, int, int);
	void addNode(UI_Node&);
	void removeNode(UI_Node&);
	void draw();
};

/*
*	UI_Panel constructor
*/
UI_Panel::UI_Panel(int x, int y, int x2, int y2){
	posX = x;
	posY = y;
	width = x2;
	height = y2;
}

/*
*	Calls draw() functions of all nodes on the panel (and the panel itself)
*/
void UI_Panel::draw() {
	//draw Panel here

	//
	for (UI_Node x : nodes) {
		x.draw();
	}
}

/*
*	Adds nodes to the panel list
*/
void UI_Panel::addNode(UI_Node &node) {
	if (!nodes.size() < UI_MAX_NODES) {
		nodes.push_back(node);
	}
	else {
		printMsg(MSG_ERROR, "Node '" + node.getName() + "' not added. nodeCount too high.");
	}
}

/*
*	Removes a specific Node from the list
*/
void UI_Panel::removeNode(UI_Node &node) {
	for (std::vector<UI_Node>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
		if (*i == node) {
			nodes.erase(i);
		}
	}
}

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
	UI_Panel &parent;
	std::string name = "Button";
public:
	void onClick(void(*));
	void draw();
	UI_Button(UI_Panel&, int, int, int, int, std::string);
};

void UI_Button::onClick(void(*func)) {
	action = func;
}

UI_Button::UI_Button(UI_Panel &pan, int x, int y, int width, int height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	pan.addNode(*this);
}

void UI_Button::draw() {

}