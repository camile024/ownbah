#include "UI_Textbox.h"

/*
*	Textbox constructor
*	pan - panel the button belongs to
*	x,y,width,heigh - starting coords (left-top) and size
*/
UI_Textbox::UI_Textbox(UI_Panel &pan, float x, float y, float width, float height) : parent(pan) {
	posX = x;
	posY = y;
	this->width = width;
	this->height = height;
	font = GLUT_BITMAP_9_BY_15;
	text = "";
	pan.addNode(*this);
}

void UI_Textbox::onClick() {
	state = TXT_SELECTED;
}

void UI_Textbox::setFont(void* font) {
	this->font = font;
}

void UI_Textbox::setText(std::string txt) {
	text = txt;
}

std::string UI_Textbox::getText() {
	return text;
}

void UI_Textbox::addText(std::string txt) {
	text += txt;
}

/*
*	Sets the state
*/
void UI_Textbox::setState(byte s) {
	state = s;
}

/*
*	Gets the state
*/
byte UI_Textbox::getState() {
	return state;
}

/*
*	Sets color for the text
*	BEWARE: USE 0.0-1.0 RANGE!
*	For 0-255 values use setColorRGB
*/
void UI_Textbox::setColor(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

/*
*	Sets color for the text (0-255 format)
*/
void UI_Textbox::setColorRGB(int r, int g, int b) {
	color.r = r / 255.00;
	color.g = g / 255.00;
	color.b = b / 255.00;
}

/*
*	Draws dope textboxes
*/
void UI_Textbox::draw() {
	/* Array with coordinates for the button */
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	float arr[] = {
		x, y, 0,
		x + width, y, 0,
		x + width, y + height, 0,
		x, y + height, 0,
	};
	/* Start doing the array drawing for the button body */
	glEnableClientState(GL_VERTEX_ARRAY);
	/* Define color depending on the button state */
	switch (state) {
	case TXT_HOVER:
	case TXT_SELECTED:
	case TXT_IDLE:
		glColor4f(color.r, color.g, color.b, 255);
		break;
	case TXT_DOWN:
		glColor4f(color.r / 2, color.g / 2, color.b / 2, 100);
		break;
	case TXT_DISABLED:
		glColor4f(color.r, color.g, color.b, 170);
		break;
	}
	/* Draw the body */
	glVertexPointer(3, GL_FLOAT, 0, arr);
	glDrawArrays(GL_POLYGON, 0, 4);

	/* ---Draw outline ---*/
	glLineWidth(1);
	if (state == BTN_HOVER) {
		glColor4f(1, 0, 0, 1);
		state = BTN_ACTIVE; //sets state back in case mouse goes out of range
	} else {
		glColor4f(0, 0, 0, 1);
	}
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	/* ---Draw text---*/
	if (state == TXT_SELECTED) {
		drawString(font, text + "_", x + width / 15, y + 20);
	} else {
		drawString(font, text, x + width / 15, y + 20);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}