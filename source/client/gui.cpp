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

===========
== PANEL ==
===========

*/
/*
*	UI_Panel constructor
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
		glVertex3f(posX + width, posY - height, 0);
		//printMsg(MSG_LOG, "Added point at " + std::to_string(posX + width) + ", " + std::to_string(posY + height));
		glVertex3f(posX, posY - height, 0);
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
void UI_Panel::addNode(UI_Node *node) {
	if (nodes.size() < UI_MAX_NODES) {
		nodes.push_back(node);
	}
	else {
		printMsg(MSG_ERROR, "Node '" + node->getName() + "' not added. nodeCount too high.");
	}
}

/*
*	Removes a specific Node from the list
*/
void UI_Panel::removeNode(UI_Node *node) {
	for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
		if (*i == node) {
			nodes.erase(i);
		}
	}
}

/*

============
== BUTTON ==
============

*/

void UI_Button::onClick(void(*func)) {
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

UI_Button::UI_Button(UI_Panel *pan, float x, float y, float width, float height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	pan->addNode(this);
}

/*
*	Sets the state of the button
*/
void UI_Button::setState(byte s) {
	state = s;
}

void UI_Button::draw() {
	glBegin(GL_POLYGON);
	switch (state) {
		case BTN_ACTIVE:
				glColor4f(color.r, color.g, color.b, 255);
			break;
		case BTN_DOWN:

			break;
		case BTN_DISABLED:
				glColor4f(color.r, color.g, color.b, 170);
			break;
	}
	float x = posX + parent->getX();
	float y = parent->getY() - posY;
	float cornerOffset = 0.02;
	glVertex3f(x, y-cornerOffset, 0);
	glVertex3f(x + cornerOffset, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y - height + cornerOffset, 0);
	glVertex3f(x + width - cornerOffset, y - height, 0);
	glVertex3f(x, y - height, 0);
	glEnd();

	/* ---Draw outline ---*/
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
	glColor4f(0, 0, 0, 255);
	if (state == BTN_DOWN) {
		glColor4f(100, 100, 100, 190);
	}
	glVertex3f(x, y - cornerOffset, 0);
	glVertex3f(x + cornerOffset, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y - height + cornerOffset, 0);
	glVertex3f(x + width - cornerOffset, y - height, 0);
	glVertex3f(x, y - height, 0);
	glEnd();
}