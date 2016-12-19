/*
TITLE SCREEN (logging in)
Author: Kamil
*/
#pragma once

#include "title.h"
#include "options.h"



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
static UI_Button *ui_host; //host game button
static UI_Button *ui_options; //options button
static UI_Button *ui_exit; //exit button
static const int MIN_WINDOW_WIDTH = 350;
static const int MIN_WINDOW_HEIGHT = 400;
static const int MAX_WINDOW_WIDTH = 500;
static const int MAX_WINDOW_HEIGHT = 700;
using namespace title;

/*
*	==========================
*	==========================
*	== NON-STATIC FUNCTIONS ==
*	==========================
*	==========================
*/	

namespace title {
	/*
	*	Call this to display the title window for the
	*	first time (intiializes GLUT)
	*/
	void create() {
		//loadSettings();
		//loadAccData(); //if settings store userAcc data
		window();
	}

	/*
	*	Goes back to the init window from a previous one
	*	(use instead of title::Create() if title::Create() has been called before)
	*/
	void show() {
		glutSetWindowTitle("The Risk");
		windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
		windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 4 + 200;
		glutReshapeWindow(windowSizeX, windowSizeY);
		init();
		//options::freeUI();
		glutDisplayFunc(display);
		glutMouseFunc(mouseInput);
		glutPassiveMotionFunc(mouseMove);
		display();
	}


	/*
	*	Frees memory of all the UI objects (static globals with 'ui_' prefix)
	*/
	void freeUI() {
		delete ui_title;
		delete ui_menu;
		delete ui_play;
		delete ui_options;
		delete ui_host;
		delete ui_exit;
	}
}

void exit() {
	exit(0);
}



/*
*	==========================
*	==========================
*	==   STATIC FUNCTIONS   ==
*	==========================
*	==========================
*/

/*
*	All the drawing goes here
*	Author: Kamil
*/
static void display() {
	printMsg(MSG_LOG, "Scene redrawn.");
	bool windowChanged = false;
	/*	Get current window sizes and change them accordingly
	If window sizes have changed, make sure to recreate objects accordingly
	*/
	windowChanged = reshapeWindow(windowSizeX, windowSizeY, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT,
		MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
	/*Clear the window*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Set the viewport and projection matrix accordingly*/
	glViewport(0, 0, windowSizeX, windowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowSizeX, windowSizeY, 0, -1.0, 1.0);
	/*Resize resolution-adjusted items*/
	if (windowChanged) {
		ui_title->setSizes(0, 0, windowSizeX, windowSizeY / 4);
		ui_menu->setSizes(windowSizeX / 5, windowSizeY / 4 + 35, windowSizeX / 5 * 3, windowSizeY / 4 * 3 - 70);
		ui_play->setSizes(15, 10, windowSizeX / 5 * 3 - 30, 30);
		ui_host->setSizes(15, 55, windowSizeX / 5 * 3 - 30, 30);
		ui_options->setSizes(15, 100, windowSizeX / 5 * 3 - 30, 30);
		ui_exit->setSizes(15, 145, windowSizeX / 5 * 3 - 30, 30);
	}

	/*Do the actual drawing*/
	ui_title->setColorRGB(228, 151, 37, 170);
	ui_menu->setColorRGB(255, 193, 100, 100);
	ui_title->draw();
	ui_menu->draw();
	glutSwapBuffers();
}


static void settings() {
	//glutDisplayFunc(NULL);
	glutMouseFunc(NULL);
	glutPassiveMotionFunc(NULL);
	//title::freeUI();
	options::show();
}

/*
*	Initialising OpenGL inside Glut
*	Author: Kamil
*/
static void init() {
	glClearColor(0.0f / 255, 0.0f / 255, 0.0f / 255, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	title::freeUI(); //Free memory of UI items in case they already exist
	ui_title = new UI_Panel(0, 0, windowSizeX, windowSizeY / 4);
	ui_menu = new UI_Panel(windowSizeX / 5, windowSizeY / 4 + 35, windowSizeX / 5 * 3, windowSizeY / 4 * 3 - 70);
	ui_play = new UI_Button(*ui_menu, 15, 10, windowSizeX / 5 * 3 - 30, 30, "Join game");
	ui_host = new UI_Button(*ui_menu, 15, 55, windowSizeX / 5 * 3 - 30, 30, "Host a server");
	ui_options = new UI_Button(*ui_menu, 15, 100, windowSizeX / 5 * 3 - 30, 30, "Options");
	ui_exit = new UI_Button(*ui_menu, 15, 145, windowSizeX / 5 * 3 - 30, 30, "Exit");
	/*Set onClick actions*/
	ui_play->setAction(login);
	ui_options->setAction(settings);
	ui_exit->setAction(exit);
	//glMatrixMode(GL_MODELVIEW);

}


/*
*	Initialising title window and glut
*	Author: Kamil
*/
static void window(){
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
	glutCreateWindow("The Risk");
	init();
	/* Anti-aliasing for drawing lines */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	/*Redirect glut to specific functions*/
	glutDisplayFunc(display);
	glutMouseFunc(mouseInput);
	glutPassiveMotionFunc(mouseMove);
	display();
	//glutIdleFunc(drawUI);
	glutMainLoop();
	
}

/*
*	Handles mouse input
*/
static void mouseInput(int key, int state, int x, int y) {
	if (key == GLUT_LEFT_BUTTON) {
		/* The following piece of code iterates over all the nodes in "ui_menu" object 
			and checks if they're within given X,Y coordinates. */

		/* get nodes of the panel */
		std::vector<UI_Node*>& nodes = ui_menu->getNodes();
		/* iterate over said nodes */
		if (nodes.size() > 0) {
			for (auto i = nodes.begin(); i != nodes.end(); ++i) {
				/* check if the clicked area is within node's coordinates */
				if (withinCoords(x, y, *i)) {
					/* button event handling*/
					UI_Button * btn = dynamic_cast<UI_Button*>(*i); //dynamic cast node->button
					if (btn != nullptr) { //if cast was successfull (meaning this indeed is a button)
						if (state == GLUT_DOWN) { //if mouseDown
							btn->setState(BTN_DOWN);
						}
						else if (btn->getState() == BTN_DOWN) { //if mouse released
							btn->setState(BTN_ACTIVE);
							btn->onClick();
						}
						printMsg(MSG_LOG, "Clicked a button.");
					}
					/* Insert any other GUI elements handling under this comment */
				}
			}
		}
	}
	glutPostRedisplay();
}

/*
*	Handles moving the mouse and hovering over objects
*/
static void mouseMove(int x, int y) {
	std::vector<UI_Node*>& nodes = ui_menu->getNodes();
	if (nodes.size() > 0){
		for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
			UI_Button * btn = dynamic_cast<UI_Button*>(*i);
			if (btn != nullptr) {
				if (withinCoords(x, y, *i)) {
					btn->setState(BTN_HOVER);
				}
				else {
					if (btn->getState() != BTN_DISABLED) {
						btn->setState(BTN_ACTIVE);
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

static void login() {
	printMsg(MSG_LOG, "Logging in...");
}

