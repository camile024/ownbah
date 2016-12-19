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
#include "../clientDebug.h"
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
*	Makes sure the window is within a reasonable size
*	Lets the drawing function know if the sizes have changed
*	since the last display() call
*/
bool reshapeWindow(int &windowSizeX, int &windowSizeY, int minWidth, int minHeight, int maxWidth, int maxHeight) {
	if (windowSizeX != glutGet(GLUT_WINDOW_WIDTH)
		|| windowSizeY != glutGet(GLUT_WINDOW_HEIGHT)) {
		windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
		windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);
		if (windowSizeY < minHeight) {
			glutReshapeWindow(windowSizeX, minHeight);
		}
		else if (windowSizeY > maxHeight) {
			glutReshapeWindow(windowSizeX, maxHeight);
		}

		if (windowSizeX < minWidth) {
			glutReshapeWindow(minWidth, windowSizeY);
		}
		else if (windowSizeX > maxWidth) {
			glutReshapeWindow(maxWidth, windowSizeY);
		}
		return true;
	}
	return 0;
}









