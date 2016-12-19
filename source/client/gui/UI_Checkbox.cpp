#include "UI_Checkbox.h"
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
void UI_Checkbox::setAction(void(*func)()) {
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