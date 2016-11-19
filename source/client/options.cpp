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






/*
*	Initialising OpenGL inside Glut
*	Author: Kamil
*/
static void init() {
	glClearColor(0.0f / 255, 0.0f / 255, 0.0f / 255, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	freeTitleUIObjects();
	freeOptionsUIObjects(); //Free memory of UI items in case they already exist
	ui_settings = new UI_Panel(0, 0, windowSizeX, windowSizeY);
	ui_window = new UI_Panel(0, 0, windowSizeX, windowSizeY / 4 * 2);
	ui_account = new UI_Panel(0, windowSizeY / 4 * 2, windowSizeX, windowSizeY / 4);
	ui_buttons = new UI_Panel(0, windowSizeY / 4 * 3, windowSizeX, windowSizeY / 4);
	ui_save = new UI_Button(*ui_buttons, 15, 10, windowSizeX / 9 * 3, 30, "Save");
	ui_cancel = new UI_Button(*ui_buttons, 15 + windowSizeX / 2, 10, windowSizeX / 9 * 3, 30, "Cancel");
	/*Set onClick actions*/
	//ui_play->setAction(login);
	//ui_options->setAction(options);
	//ui_exit->setAction(exit);
	//glMatrixMode(GL_MODELVIEW);

}

/*
*	All the drawing goes here
*	Author: Kamil
*/
void optionsDisplay(void) {
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
*	Initialising title window and glut
*	Author: Kamil
*/
static void window() {
	/*Fake arguments to pass to glutInit()*/
	int argc = 1;
	char *argv[1];
	argv[0] = "1";
	/*Get resolution of the screen*/
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	/*Create a reasonably sized window*/
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutInitWindowPosition(screenX / 2.8, screenY / 2 - windowSizeY / 1.5);
	glutCreateWindow("Options");
	init();
	/*Redirect glut to specific functions*/
	glutDisplayFunc(optionsDisplay);
		//glutMouseFunc(mouseInput);
		//glutPassiveMotionFunc(mouseMove);
	optionsDisplay();
	//glutIdleFunc(drawUI);
	glutMainLoop();

}

/*
*	Call this to display the options window
*/
void optionsCreate() {
	//loadSettings();
	//loadAccData(); //if settings store userAcc data
	window();
}

/*
*	Frees memory of all the UI objects (static globals with 'ui_' prefix)
*/
void freeOptionsUIObjects() {
	free(ui_window);
	free(ui_account);
	free(ui_save);
	free(ui_cancel);

}
