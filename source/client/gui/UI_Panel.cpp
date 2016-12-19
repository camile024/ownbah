#include "UI_Panel.h"
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
UI_Panel::UI_Panel(float x, float y, float x2, float y2) {
	posX = x;
	posY = y;
	width = x2;
	height = y2;
	style = STYLE_ROUND;
	flags = 0;
}

void UI_Panel::addFlag(int flag) {
	flags |= flag;
}

void UI_Panel::removeFlag(int flag) {
	flags |= ~flag;
}

bool UI_Panel::checkFlag(int flag) {
	return ((flag & flags) == flag);
}

/*
*	Calls draw() functions of all nodes on the panel (and the panel itself)
*/
void UI_Panel::draw() {
	/*Draws the panel itself*/
	float cornerOffset = 5;
	float varray[30];
	int count;
	switch (style) {
		case STYLE_ROUND: 
		{
			float temp[] = {
				posX, posY + cornerOffset, 0,
				posX + cornerOffset, posY, 0,
				posX + width - cornerOffset, posY, 0,
				posX + width, posY + cornerOffset, 0,
				posX + width, posY + height - cornerOffset, 0,
				posX + width - cornerOffset, posY + height, 0,
				posX + cornerOffset, posY + height, 0,
				posX, posY + height - cornerOffset, 0,
			};
			count = 8;
			std::copy(temp, temp + sizeof(temp) / sizeof(temp[0]), varray);
		}
		break;
		case STYLE_NORMAL:
		{
			float temp2[] = {
				posX, posY, 0,
				posX + width, posY, 0,
				posX + width, posY + height, 0,
				posX, posY + height, 0,
			};
			count = 4;
			std::copy(temp2, temp2 + sizeof(temp2) / sizeof(temp2[0]), varray);
		}
		break;

	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, varray);
	glColor4f(color.r, color.g, color.b, color.a);
	glDrawArrays(GL_POLYGON, 0, count);
	if (checkFlag(STYLEFLAG_OUTLINE)) {
		glDrawArrays(GL_LINE_LOOP, 0, count);
		glColor4f(0, 0, 0, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);

	/* Draw the nodes inside panel */
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

