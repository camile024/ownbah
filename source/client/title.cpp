/*
TITLE SCREEN (logging in)
Author: Kamil
*/
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

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void window(int argc, char** argv){
	glutInit(&argc, argv);
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenX / 8 + 200, screenY / 4 + 200);
	glutInitWindowPosition(screenX / 2 - screenX / 8 - 100, screenY / 2 - screenY / 4);
	glutCreateWindow("Title window");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}