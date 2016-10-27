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


/*

============
== GENERAL==
============


/*

===========
== PANEL ==
===========

*/
/*
*	UI_Panel constructor
*	x,y - coordinates inside window (left-top corner of panel)
*	x2,y2 - width and height of the window (don't confuse with 
*		coordinates of the opposite corner!)
*/
UI_Panel::UI_Panel(float x, float y, float x2, float y2){
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
	glBegin(GL_QUADS);
	{
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex3f(posX, posY, 0);
		//printMsg(MSG_LOG, "Added point at " + std::to_string(posX) + ", " + std::to_string(posY));
		glVertex3f(posX + width, posY, 0);
		//printMsg(MSG_LOG, "Added point at " + std::to_string(posX + width) + ", " + std::to_string(posY));
		glVertex3f(posX + width, posY + height, 0);
		//printMsg(MSG_LOG, "Added point at " + std::to_string(posX + width) + ", " + std::to_string(posY + height));
		glVertex3f(posX, posY + height, 0);
		//printMsg(MSG_LOG, "Added point at " + std::to_string(posX) + ", " + std::to_string(posY + height));
	}
	glEnd();
	//
	for (UI_Node* x : nodes) {
		x->draw();
	}
}

/*
*	Sets a color for button
*	BEWARE: USE 0.0-1.0 RANGE!
*	For 0-255 values use setColorRGB
*/
void UI_Panel::setColor(float r, float g, float b, float a) {
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

/*
*	Sets a color for a button (0-255 format)
*/
void UI_Panel::setColorRGB(int r, int g, int b, int a) {
	color.r = r / 255.00;
	color.g = g / 255.00;
	color.b = b / 255.00;
	color.a = a / 255.00;
}

/*
*	Adds nodes to the panel list
*/
void UI_Panel::addNode(UI_Node &node) {
	if (nodes.size() < UI_MAX_NODES) {
		nodes.push_back(&node);
	}
	else {
		printMsg(MSG_ERROR, "Node '" + node.getName() + "' not added. nodeCount too high.");
	}
}

/*
*	Removes a specific Node from the list (untested)
*/
void UI_Panel::removeNode(UI_Node &node) {
	for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
		if (*i == &node) {
			nodes.erase(i);
		}
	}
}

/*
*	Returns a vector with all the nodes of the panel (not tested)
*/
std::vector<UI_Node*>& UI_Panel::getNodes() {
	return nodes;
}

/*

============
== BUTTON ==
============

*/

/*
* Runs the action
*/
void UI_Button::onClick() {
	if (action != nullptr) {
		action();
	}
}

/*
*	Sets the action to a specified function
*/
void UI_Button::setAction(void (*func)()) {
	action = func;
}
/*
*	Sets a color for button
*	BEWARE: USE 0.0-1.0 RANGE!
*	For 0-255 values use setColorRGB
*/
void UI_Button::setColor(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

/*
*	Sets a color for a button (0-255 format)
*/
void UI_Button::setColorRGB(int r, int g, int b) {
	color.r = r / 255.00;
	color.g = g / 255.00;
	color.b = b / 255.00;
}

/*
*	Button constructor
*	pan - panel the button belongs to
*	x,y,width,heigh - starting coords (left-top) and size
*	caption - caption
*/
UI_Button::UI_Button(UI_Panel &pan, float x, float y, float width, float height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	pan.addNode(*this);
}

/*
*	Sets the state of the button
*/
void UI_Button::setState(byte s) {
	state = s;
}

/*
*	Draws dope buttons
*	Needs putting all the vertices into a single array
*		for readability
*/
void UI_Button::draw() {
	/* Array with coordinates for the button */
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	float cornerOffset = 5.0f;
	float arr[] = {
		x, y + cornerOffset, 0,
		x + cornerOffset, y, 0,
		x + width, y, 0,
		x + width, y + height - cornerOffset, 0,
		x + width - cornerOffset, y + height, 0,
		x, y + height, 0,
	};
	/* Start doing the array drawing for the button body */
	glEnableClientState(GL_VERTEX_ARRAY);
	/* Define color depending on the button state */
	switch (state) {
		case BTN_ACTIVE:
				glColor4f(color.r, color.g, color.b, 255);
			break;
		case BTN_DOWN:
				glColor4f(color.r/2, color.g/2, color.b/2, 100);
			break;
		case BTN_DISABLED:
				glColor4f(color.r, color.g, color.b, 170);
			break;
	}
	/* Draw the body */
	glVertexPointer(3, GL_FLOAT, 0, arr);
	glDrawArrays(GL_POLYGON, 0, 6);

	/* ---Draw outline ---*/
	glLineWidth(1);
	glColor4f(0, 0, 0, 255);
	if (state == BTN_DOWN) {
		glColor4f(100, 100, 100, 190);
	}
	glDrawArrays(GL_LINE_LOOP, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
}