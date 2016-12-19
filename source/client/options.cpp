/*
OPTIONS SCREEN (settings)
Author: Kamil
*/
#pragma once


#include "options.h"
#include "title.h"

/*
*
*	WINDOW GLOBALS
*
*/
static int windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
static int windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 4 + 200;
static UI_Panel *ui_settings; //settings panel
static UI_Panel *ui_window; //window settings panel
static UI_Panel *ui_buttons; //bottom panel
static UI_Panel *ui_account; //account settings panel
static UI_Button *ui_save; //saves options into the file, applies to variables
static UI_Button *ui_cancel; //cancels changes made
//static UI_Combobox *ui_resolutions;
//static UI_Checkbox *ui_fullscreen;
//static UI_Checkbox *ui_saveUsername;
//static UI_Checkbox *ui_savePassword;
static const int MIN_WINDOW_WIDTH = 350;
static const int MIN_WINDOW_HEIGHT = 400;
static const int MAX_WINDOW_WIDTH = 500;
static const int MAX_WINDOW_HEIGHT = 700;

/*
*	GLOBAL GLOBALS
*
*
*/
int g_resX;
int g_resY;
bool g_saveUsername;
bool g_savePassword;
bool g_fullScreen;


namespace options {

	/*
	*	Call this to display the options window
	*/
	void show() {
		//loadSettings();
		//loadAccData(); //if settings store userAcc data
		windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
		windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 4 + 200;
		glutReshapeWindow(windowSizeX, windowSizeY);
		init();
		glutDisplayFunc(display);
		glutMouseFunc(mouseInput);
		glutPassiveMotionFunc(mouseMove);
		display();
	}

	/*
	*	Frees memory of all the UI objects (static globals with 'ui_' prefix)
	*/
	void freeUI() {
		delete ui_window;
		delete ui_account;
		delete ui_save;
		delete ui_cancel;

	}

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
static void display(void) {
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
		ui_settings->setSizes(0, 0, windowSizeX, windowSizeY);
		ui_window->setSizes(0, 0, windowSizeX, windowSizeY / 4 * 2);
		ui_account->setSizes(0, windowSizeY / 4 * 2, windowSizeX, windowSizeY / 4);
		ui_buttons->setSizes(0, windowSizeY / 4 * 3, windowSizeX, windowSizeY / 4);
		ui_save->setSizes(15, 10, windowSizeX / 9 * 3, 30);
		ui_cancel->setSizes(15 + windowSizeX / 2, 10, windowSizeX / 9 * 3, 30);
	}

	/*Do the actual drawing*/
	ui_settings->setColorRGB(255, 193, 100, 50);
	ui_buttons->setColorRGB(255, 193, 100, 100);
	ui_window->setColorRGB(255, 193, 100, 100);
	ui_account->setColorRGB(255, 193, 100, 100);
	ui_settings->draw();
	ui_buttons->draw();
	ui_window->draw();
	ui_account->draw();
	glutSwapBuffers();
}

/*
*	Initialising Options
*	Author: Kamil
*/
static void init() {
	glClearColor(0.0f / 255, 0.0f / 255, 0.0f / 255, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	options::freeUI(); //Free memory of UI items in case they already exist
	ui_settings = new UI_Panel(0, 0, windowSizeX, windowSizeY);
	ui_window = new UI_Panel(0, 0, windowSizeX, windowSizeY / 4 * 2);
	ui_account = new UI_Panel(0, windowSizeY / 4 * 2, windowSizeX, windowSizeY / 4);
	ui_buttons = new UI_Panel(0, windowSizeY / 4 * 3, windowSizeX, windowSizeY / 4);
	ui_save = new UI_Button(*ui_buttons, 15, 10, windowSizeX / 9 * 3, 30, "Save");
	ui_cancel = new UI_Button(*ui_buttons, 15 + windowSizeX / 2, 10, windowSizeX / 9 * 3, 30, "Cancel");
	/*Set onClick actions*/
	//ui_play->setAction(login);
	//ui_options->setAction(options);
	ui_cancel->setAction(cancel);
	//glMatrixMode(GL_MODELVIEW);

}


/*
*	Handles mouse input
*/
static void mouseInput(int key, int state, int x, int y) {
	if (key == GLUT_LEFT_BUTTON) {
		/* The following piece of code iterates over all the nodes in "ui_menu" object
		and checks if they're within given X,Y coordinates. */

		/* get nodes of the panel */
		std::vector<UI_Node*>& nodes = ui_buttons->getNodes();
		/* iterate over said nodes */
		for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
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
	glutPostRedisplay();
}

/*
*	Handles moving the mouse and hovering over objects
*/
static void mouseMove(int x, int y) {
	std::vector<UI_Node*>& nodes = ui_buttons->getNodes();
	if (nodes.size() > 0) {
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

/*
*	Go back to main menu
*/
static void cancel() {
	title::show();
}