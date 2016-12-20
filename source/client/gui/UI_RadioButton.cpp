#include "UI_RadioButton.h"
/*

==============
== CHECKBOX ==
==============

*/

/*
*	Same constructor as in a button
*/
UI_RadioButton::UI_RadioButton(UI_Panel &pan, float x, float y, float width, float height, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	this->caption = caption;
	group = 0;
	pan.addNode(*this);
}

/*
*	Returns current radiobutton state
*/
byte UI_RadioButton::getState() {
	return state;
}

/*
*	Sets the state for the radiobutton (same states as for buttons)
*/
void UI_RadioButton::setState(byte state) {
	this->state = state;
}

/*
*	Does the onClick event
*/
void UI_RadioButton::onClick() {
	this->check();
	if (action != nullptr) {
		action();
	}
}

/*
*	Sets the event for the radiobutton click
*/
void UI_RadioButton::setAction(void(*func)()) {
	action = func;
}

/*
*	Checks the radiobutton
*/
void UI_RadioButton::check() {
	checked = true;
}

/*
*	Unchecks the radiobutton
*/
void UI_RadioButton::unCheck() {
	checked = false;
}

/*
*	Draws the checkbox
*	(UNTESTED) + UNFINISHED
*/
void UI_RadioButton::draw() {
	/* Arrays with coordinates*/
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	float cornerOffset = 5.0f;
	float boxWidth = 15;
	float arrOut[] = {
		x, y + cornerOffset, 0,
		x + cornerOffset, y, 0,
		x + width - cornerOffset, y, 0,
		x + width, y + cornerOffset, 0,
		x + width, y + height - cornerOffset, 0,
		x + width - cornerOffset, y + height, 0,
		x + cornerOffset, y + height, 0,
		x, y + height - cornerOffset, 0,
	};

	float arrBox[] = {
		x + width / 16, y + height / 5, 0,
		x + width / 16 + boxWidth, y + height / 5, 0,
		x + width / 16 + boxWidth, y + height / 5 + boxWidth, 0,
		x + width / 16, y + height / 5 + boxWidth, 0,
	};
	float arrTick[] = {
		x + width / 16, y + height / 5 + boxWidth / 4, 0,
		x + width / 16 + boxWidth / 2, y + height / 5 + boxWidth, 0,
		x + width / 16 + boxWidth, y + height / 5 , 0,
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
	/* Draw the body+outline */
	glVertexPointer(3, GL_FLOAT, 0, arrOut);
	glDrawArrays(GL_POLYGON, 0, 8);
	if (state == BTN_HOVER)
		glColor4f(1, 0, 0, 1);
	else
		glColor4f(0, 0, 0, 1);
	glDrawArrays(GL_LINE_LOOP, 0, 8);
	/* ---Draw the circle + outline ---*/
	glVertexPointer(3, GL_FLOAT, 0, arrBox);

	if (state == BTN_DOWN) {
		glColor4f(0.5, 0.5, 0.5, 1);
	}
	else {
		glColor4f(1, 1, 1, 1);
	}
	
	drawFilledCircle(x + 18, y + 14, 7, 300);

	glLineWidth(1.5);
	if (state == BTN_HOVER) {
		glColor4f(1, 0, 0, 1);
		state = BTN_ACTIVE;
	}
	else {
		glColor4f(0, 0, 0, 1);
	}
	drawCircle(x + 18, y + 14, 7, 300);
	/* ---Draw the tick--- */
	if (checked) {
		glLineWidth(2);
		drawFilledCircle(x + 18, y + 14, 5, 300);
	}

	/* ---Draw text---*/
	drawString(GLUT_BITMAP_HELVETICA_18, caption, x + width / 15 + boxWidth + 5, y + 20);
	glDisableClientState(GL_VERTEX_ARRAY);
}
