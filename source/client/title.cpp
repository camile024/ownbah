/*
TITLE SCREEN (logging in)
Author: Kamil
*/
#pragma once
//standard includes
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>

//graphics
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GL\glut.h>

//custom headers
#include "clientDebug.h"
#include "gui.h"
#include "title.h"




/*
*	Initialising OpenGL inside Glut
*	Author: Kamil
*/
void init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 	//view angle
		1.0,    //aspect ratio
		10.0,   //near clip
		200.0); //far clip
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
*	All the drawing goes here
*	Author: Kamil
*/
static void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();     	//saves the current matrix on the top of the matrix stack
	glTranslatef(0, 0, -100); //translates the current matrix 0 in x, 0 in y and -100 in z
							  //glFlush();
}

/*
*	Initialising title window and glut
*	Author: Kamil
*/
void window(){
	int argc = 1;
	char *argv[1];
	argv[0] = "1";
	glutInit(&argc, argv);
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenX / 8 + 200, screenY / 4 + 200);
	glutInitWindowPosition(screenX / 2 - screenX / 8 - 100, screenY / 2 - screenY / 4);
	glutCreateWindow("Title");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}


/*
*	Main title loop
*	Author: Kamil
*/
void titleLoop(){
	doInput();
	doEngine();
	doDrawing();
}

void doInput() {

}

void doEngine() {

}

void doDrawing() {
	window();
	glutSwapBuffers();
}

void login(int ID) {
	printMsg(MSG_LOG, "Logging in...");
}