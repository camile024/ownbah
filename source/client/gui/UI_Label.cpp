#include "UI_Label.h"

/*
*	Sets color for the text
*	BEWARE: USE 0.0-1.0 RANGE!
*	For 0-255 values use setColorRGB
*/
void UI_Label::setColor(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

/*
*	Sets color for the text (0-255 format)
*/
void UI_Label::setColorRGB(int r, int g, int b) {
	color.r = r / 255.00;
	color.g = g / 255.00;
	color.b = b / 255.00;
}

void UI_Label::setFont(void* font) {
	this->font = font;
}

/*
*	Label constructor
*	pan - panel the button belongs to
*	x,y,width,heigh - starting coords (left-top) and size
*	caption - caption
*/
UI_Label::UI_Label(UI_Panel &pan, float x, float y, std::string caption) : parent(pan) {
	posX = x;
	posY = y;
	this->caption = caption;
	pan.addNode(*this);
	font = GLUT_BITMAP_9_BY_15;
}

/*
*	Draws dope labels
*/
void UI_Label::draw() {
	/* Array with coordinates for the button */
	float x = posX + parent.getX();
	float y = parent.getY() + posY;
	/* Define color */
	glColor4f(color.r, color.g, color.b, 255);
	/* ---Draw text---*/
	drawString(font, caption, x, y + 20);
}