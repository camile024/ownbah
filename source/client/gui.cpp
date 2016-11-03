/*
*	BASE GUI ELEMENTS
*	NEEDS MOVING 1-LINE FUNCTIONS TO GUI.H 
*	AS INLINE IMPLEMENTATION
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
*/
void drawString(void *font, std::string msg, float x, float y) {
	glRasterPos2f(x, y); 
	for (int i = 0; i < msg.length(); i++) {
		glutBitmapCharacter(font, msg[i]);
	}
}


/*
===========
== NODE ==
===========

*/

/*
*	Sets the sizes (between drawing)
*/
void UI_Node::setSizes(float x, float y, float width, float height) {
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;
}

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
	/*Draws the panel itself*/
	float cornerOffset = 5;
	float varray[] = {
		posX, posY + cornerOffset, 0,
		posX + cornerOffset, posY, 0,
		posX + width - cornerOffset, posY, 0,
		posX + width, posY + cornerOffset, 0,
		posX + width, posY + height - cornerOffset, 0,
		posX + width - cornerOffset, posY + height, 0,
		posX + cornerOffset, posY + height, 0,
		posX, posY + height - cornerOffset, 0,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, varray);
	glColor4f(color.r, color.g, color.b, color.a);
	glDrawArrays(GL_POLYGON, 0, 8);
	glDisableClientState(GL_VERTEX_ARRAY);
	/*glBegin(GL_QUADS);
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
	glEnd();*/
	//
	for (UI_Node* x : nodes) {
		x->draw();
	}

}

/*
*	Sets the sizes (between drawing)
*/
void UI_Panel::setSizes(float x, float y, float width, float height) {
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;
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
		if (**i == node) {
			nodes.erase(i);
		}
	}
}

/*
*	Returns a vector with all the nodes of the panel
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
*	Gets button's state
*/
byte UI_Button::getState() {
	return state;
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
		case BTN_HOVER:
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
	glColor4f(0, 0, 0, 1);
	if (state == BTN_DOWN) {
		glColor4f(1, 1, 1, 1);
	} else if (state == BTN_HOVER) {
		glColor4f(1, 0, 0, 1);
		state = BTN_ACTIVE; //sets state back in case mouse goes out of range
	}
	glDrawArrays(GL_LINE_LOOP, 0, 6);

	/* ---Draw text---*/
	drawString(GLUT_BITMAP_HELVETICA_18, caption, x + width / 15, y + 20);
	glDisableClientState(GL_VERTEX_ARRAY);
}

/*

==============
== CHECKBOX ==
==============

*/

/*
*	Same constructor as in a button
*/
UI_Checkbox::UI_Checkbox(UI_Panel &pan, float x, float y, float width, float height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	pan.addNode(*this);
}

/*
*	Returns current checkbox state
*/
byte UI_Checkbox::getState() {
	return state;
}

/*
*	Sets the state for the checkbox (same states as for buttons)
*/
void UI_Checkbox::setState(byte state) {
	this->state = state;
}

/*
*	Does the onClick event
*/
void UI_Checkbox::onClick() {
	this->toggle();
	if (action != nullptr) {
		action();
	}
}

/*
*	Sets the event for the checkbox click
*/
void UI_Checkbox::setAction(void (*func)()) {
	action = func;
}

/*
*	Toggles the checkbox state
*/
void UI_Checkbox::toggle() {
	checked = !checked;
}

/*
*	Draws the checkbox
*	(UNTESTED) + UNFINISHED
*/
void UI_Checkbox::draw() {
	/* Arrays with coordinates*/
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	float cornerOffset = 5.0f;
	float arrOut[] = {
		posX, posY + cornerOffset, 0,
		posX + cornerOffset, posY, 0,
		posX + width - cornerOffset, posY, 0,
		posX + width, posY + cornerOffset, 0,
		posX + width, posY + height - cornerOffset, 0,
		posX + width - cornerOffset, posY + height, 0,
		posX + cornerOffset, posY + height, 0,
		posX, posY + height - cornerOffset, 0,
	};

	float arrBox[] = {
		posX + width / 16, posY + height / 5, 0,
		posX + width / 16 * 2, posY + height / 5, 0,
		posX + width / 16 * 2, posY + height / 5 * 4, 0,
		posX + width / 16, posY + height / 5 * 4, 0,
	};
	/* Start doing the array drawing for the button body */
	glEnableClientState(GL_VERTEX_ARRAY);
	/* Define color depending on the button state */
	switch (state) {
	case BTN_HOVER:
	case BTN_ACTIVE:
		glColor4f(0, 0, 0, 255);
		break;
	case BTN_DOWN:
		glColor4f(0.5, 0.5, 0.5, 255);
		break;
	case BTN_DISABLED:
		glColor4f(0.5, 0.5, 0.5, 170);
		break;
	}
	/* Draw the outline */
	glVertexPointer(3, GL_FLOAT, 0, arrOut);
	glDrawArrays(GL_POLYGON, 0, 6);

	/* ---Draw the box ---*/
	glLineWidth(1);
	glColor4f(0, 0, 0, 1);
	if (state == BTN_DOWN) {
		glColor4f(1, 1, 1, 1);
	}
	else if (state == BTN_HOVER) {
		glColor4f(1, 0, 0, 1);
		state = BTN_ACTIVE; //sets state back in case mouse goes out of range
	}
	glDrawArrays(GL_LINE_LOOP, 0, 6);

	/* ---Draw text---*/
	drawString(GLUT_BITMAP_HELVETICA_18, caption, x + width / 15, y + 20);
	glDisableClientState(GL_VERTEX_ARRAY);
}


/*

==============
== COMBOBOX ==
==============

*/

/*
*	Same constructor as in a button/checkbox
*/
UI_Combobox::UI_Combobox(UI_Panel &pan, float x, float y, float width, float height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	pan.addNode(*this);
}

/*
*	Draws the Combobox
*	(UNTESTED) + UNFINISHED
*/
void UI_Combobox::draw() {
	/* Arrays with coordinates */
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	float arrBox[] = {
		x + width, y, 0,
		x + width, y, 0,
		x + width, y + height, 0,
		x, y + height, 0,
	};

	/* Start doing the array drawing for the button body */
	glEnableClientState(GL_VERTEX_ARRAY);
	/* Define color depending on the button state */
	switch (state) {
	case BTN_HOVER:
	case BTN_ACTIVE:
		glColor4f(0, 0, 0, 255);
		break;
	case BTN_DOWN:
		glColor4f(1, 1, 1, 255);
		break;
	case BTN_DISABLED:
		glColor4f(0.5, 0.5, 0.5, 170);
		break;
	}

	/* Draw the body */
	glVertexPointer(3, GL_FLOAT, 0, arrBox);
	glDrawArrays(GL_POLYGON, 0, 4);

	/* Draw the items */
	if (state == BTN_DOWN && items.size() > 0) {
		float j = 0;
		for (int i = start; i <= end; i++) {
			float itemArr[] =
			{
				x, y + height * j, 0,
				x + width, y + height * j, 0,
				x + width, y + height * j + height, 0,
				x, y + height * j + height, 0
			};
			glColor4f(1, 1, 1, 255);
			glVertexPointer(3, GL_FLOAT, 0, itemArr);
			glDrawArrays(GL_POLYGON, 0, 4);
			drawString(GLUT_BITMAP_HELVETICA_18, getSelected(i), x + width / 15, y + (height * j) + 20);
			glDisableClientState(GL_VERTEX_ARRAY);
			j++;
		}
	}
	/* Draw the outline */
	glColor4f(0, 0, 0, 255);
	glVertexPointer(3, GL_FLOAT, 0, arrBox);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	/* ---Draw text---*/
	drawString(GLUT_BITMAP_HELVETICA_18, caption, x + width / 15, y + 20);
	glDisableClientState(GL_VERTEX_ARRAY);
}

/*
*	Adds an item to the checkbox
*/
void UI_Combobox::addItem(std::string *s) {
	items.push_back(s);
}

/*
*	Removes a specific item from items
*/
void UI_Combobox::removeItem(std::string *s) {
	for (auto i = items.begin(); i != items.end(); ++i) {
		if (*s == **i) {
			items.erase(i);
		}
	}
}