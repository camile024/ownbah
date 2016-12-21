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

/*
*	Draws a circle
*	Credit: http://slabode.exofire.net/circle_draw.shtml
*/
void drawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 

								   //calculate the tangential vector 
								   //remember, the radial vector is (x, y) 
								   //to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

/*
*	Draws a filled circle
*	Credit: http://slabode.exofire.net/circle_draw.shtml
*/
void drawFilledCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 

								   //calculate the tangential vector 
								   //remember, the radial vector is (x, y) 
								   //to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}





