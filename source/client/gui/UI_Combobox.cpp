#include "UI_Combobox.h"
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
	font = GLUT_BITMAP_9_BY_15;
	pan.addNode(*this);
}

void UI_Combobox::setFont(void* font) {
	this->font = font;
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