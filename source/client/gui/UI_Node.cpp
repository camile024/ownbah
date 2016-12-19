#include "UI_Node.h"
/*
===========
== NODE ==
===========

*/

/*
*	Checks if 'x' and 'y' are within coordinates of 'a'
*/
bool withinCoords(int x, int y, UI_Node* a) {
	int parentX = a->getParent().getX();
	int parentY = a->getParent().getY();
	int itemX = a->getX();
	int itemY = a->getY();
	int width = a->getWidth();
	int height = a->getHeight();
	return (
		x > parentX + itemX && x < parentX + itemX + width &&
		y > parentY + itemY && y < parentY + itemY + height
		);
}

/*
*	Sets the sizes (between drawing)
*/
void UI_Node::setSizes(float x, float y, float width, float height) {
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;
}