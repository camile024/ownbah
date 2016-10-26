/*
TITLE SCREEN (logging in)
Author: Kamil
TODO: make items persistent, recreate only
	if window has changed (so the scene doesn't
	overwrite the button with "BTN_DOWN" state
	if it's clicked).
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
*
*	WINDOW GLOBALS
*
*/
static int windowSizeX = GetSystemMetrics(SM_CXSCREEN)/5;
static int windowSizeY = GetSystemMetrics(SM_CYSCREEN)/4+200;
static UI_Panel *ui_title; //title graphic/logo
static UI_Panel *ui_menu; //menu panel
static UI_Button *ui_play; //play/join game button
static UI_Button *ui_options; //options button

/*
*	Initialising OpenGL inside Glut
*	Author: Kamil
*/
void init(){
	glClearColor(133.00f/255, 160.00f/255, 242.00f/255, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	//glMatrixMode(GL_MODELVIEW);
	
}

/*
*	All the drawing goes here
*	Author: Kamil
*/
static void display(void) {
	printMsg(MSG_LOG, "Scene redrawn.");
	/*Get current window sizes*/
	windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
	windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);
	/*Clear the window*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Set the viewport and projection matrix accordingly*/
	glViewport(0, 0, windowSizeX, windowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowSizeX, windowSizeY, 0, -1.0, 1.0);
	/*Free memory of UI items in case they already exist*/
	freeTitleUIObjects();
	/*Initialise resolution-adjusted items*/
	ui_title = new UI_Panel(0, 0, windowSizeX, windowSizeY / 4);
	ui_menu = new UI_Panel(windowSizeX / 5, windowSizeY / 4 + 35, windowSizeX / 5 * 3, windowSizeY / 4 * 3 - 70);
	ui_play = new UI_Button(*ui_menu, 15, 10, windowSizeX / 5 * 3 - 30, 30, "Play");
	ui_options = new UI_Button(*ui_menu, 15, 55, windowSizeX / 5 * 3 - 30, 30, "Options");
	
	/*Do the actual drawing*/
	ui_title->setColorRGB(228, 151, 37, 170);
	ui_menu->setColorRGB(255, 193, 100, 100);
	ui_title->draw();
	ui_menu->draw();
	glutSwapBuffers();
}

/*
*	Initialising title window and glut
*	Author: Kamil
*/
void window(){
	/*Fake arguments to pass to glutInit()*/
	int argc = 1;
	char *argv[1];
	argv[0] = "1";
	/*Init glut*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	/*Get resolution of the screen*/
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	/*Create a reasonably sized window*/
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutInitWindowPosition(screenX / 2.8, screenY / 2 - windowSizeY / 1.5);
	glutCreateWindow("Title");
	init();
	/*Redirect glut to specific functions*/
	glutDisplayFunc(display);
	glutMouseFunc(mouseInput);
	glutMainLoop();
}

/*
*	Call this to display the title window
*/
void titleCreate(){
	window();
}

/*
*	Handles mouse input
*/
void mouseInput(int key, int state, int x, int y) {
	if (state == GLUT_DOWN && key == GLUT_LEFT_BUTTON) {
		std::vector<UI_Node*>& nodes = ui_menu->getNodes();
		for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
			if (withinCoords(x, y, *i)) {
				UI_Button * btn = dynamic_cast<UI_Button*>(*i);
				if (btn != nullptr) {
					btn->setState(BTN_DOWN);
					glutPostRedisplay();
					printMsg(MSG_LOG, "Clicked a button.");
				}
			}
		}
	}
}

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


void doDrawing() {
	
}

void login(int ID) {
	printMsg(MSG_LOG, "Logging in...");
}

/*
*	Frees memory of all the UI objects (static globals with 'ui_' prefix)
*/
void freeTitleUIObjects() {
	free(ui_title);
	free(ui_menu);
	free(ui_play);
	free(ui_options);
}