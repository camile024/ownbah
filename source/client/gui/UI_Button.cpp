#include "UI_Button.h"

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
void UI_Button::setAction(void(*func)()) {
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
	font = GLUT_BITMAP_9_BY_15;
	pan.addNode(*this);
}

void UI_Button::setFont(void* font) {
	this->font = font;
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
		glColor4f(color.r / 2, color.g / 2, color.b / 2, 100);
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
	drawString(font, caption, x + width / 15, y + 20);
	glDisableClientState(GL_VERTEX_ARRAY);
}