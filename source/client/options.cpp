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
static bool windowActive = true;
static int windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
static int windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 5;
static UI_Panel *ui_settings; //settings panel
static UI_Panel *ui_window; //window settings panel
static UI_Panel *ui_buttons; //bottom panel
static UI_Panel *ui_account; //account settings panel
static UI_Button *ui_save; //saves options into the file, applies to variables
static UI_Button *ui_cancel; //cancels changes made
//static UI_Combobox *ui_resolutions;
static UI_RadioButton *ui_res1024;
static UI_RadioButton *ui_res1280;
static UI_RadioButton *ui_res1600;
static UI_RadioButton *ui_res1920;
static UI_Checkbox *ui_fullscreen;
static UI_Checkbox *ui_saveUsername;
static UI_RadioButton *lastRadioButton;

//static UI_Checkbox *ui_savePassword;
static const int MIN_WINDOW_WIDTH = 370;
static const int MIN_WINDOW_HEIGHT = 400;
static const int MAX_WINDOW_WIDTH = 400;
static const int MAX_WINDOW_HEIGHT = 400;
static float scaleX = windowSizeX / 10;
static float scaleY = windowSizeY / 10;
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
		glutSetWindowTitle("Settings");
		windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
		windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 5 ;
		glutReshapeWindow(windowSizeX, windowSizeY);
		scaleX = windowSizeX / 10;
		scaleY = windowSizeY / 10;
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
		delete ui_settings;
		delete ui_buttons;
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
	/*Clear the window*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*Set the viewport and projection matrix accordingly*/
	glViewport(0, 0, windowSizeX, windowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowSizeX, windowSizeY, 0, -1.0, 1.0);
	/*Resize resolution-adjusted items*/
	/*	Get current window sizes and change them accordingly
	If window sizes have changed, make sure to resize them
	*/
	windowChanged = reshapeWindow(windowSizeX, windowSizeY, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT,
		MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
	if (windowChanged) {
		scaleX = windowSizeX / 10;
		scaleY = windowSizeY / 10;
		ui_settings->setSizes(0, 0, windowSizeX, windowSizeY);
		ui_window->setSizes(0, 0, windowSizeX, scaleY * 5);
		ui_account->setSizes(0, scaleY * 5, windowSizeX, scaleY * 3);
		ui_buttons->setSizes(0, scaleY * 8, windowSizeX, scaleY * 2);
		ui_save->setSizes(15, 10, scaleX * 4.5, 30);
		ui_cancel->setSizes(30 + scaleX * 4.5, 10, scaleX * 4.5, 30);
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
	/* Main Panel */
	ui_settings = new UI_Panel(0, 0, windowSizeX, windowSizeY);
	/* Window Settings */
	ui_window = new UI_Panel(0, 0, windowSizeX, scaleY * 5);
	ui_fullscreen = new UI_Checkbox(*ui_window, 15, 10, scaleX * 4, 30, "Full Screen");
	ui_res1024 = new UI_RadioButton(*ui_window, 15, 50, scaleX * 4, 30, "1024x576");
	ui_res1280 = new UI_RadioButton(*ui_window, 30 + scaleX * 4, 50, scaleX * 4, 30, "1280x720");
	ui_res1600 = new UI_RadioButton(*ui_window, 15, 100, scaleX * 4, 30, "1600x900");
	ui_res1920 = new UI_RadioButton(*ui_window, 30 + scaleX * 4, 100, scaleX * 4, 30, "1920x1080");
	/* Account Settings */
	ui_account = new UI_Panel(0, scaleY * 5, windowSizeX, scaleY * 3);
	ui_saveUsername = new UI_Checkbox(*ui_account, 15, 10, windowSizeX / 9 * 4, 30, "Save Username");
	ui_saveUsername = new UI_Checkbox(*ui_account, 25 + windowSizeX / 9 * 4, 10, windowSizeX / 9 * 4, 30, "Save Password");
	/* Bottom Buttons */
	ui_buttons = new UI_Panel(0, scaleY * 8, windowSizeX, scaleY * 2);
	ui_save = new UI_Button(*ui_buttons, 15, 10, scaleX * 4.5, 30, "Save");
	ui_cancel = new UI_Button(*ui_buttons, 30 + scaleX * 4.5, 10, scaleX * 4.5, 30, "Cancel");

	/* Panel styles */
	ui_settings->setStyle(STYLE_NORMAL);
	ui_window->setStyle(STYLE_NORMAL);
	ui_account->setStyle(STYLE_NORMAL);
	ui_buttons->setStyle(STYLE_NORMAL);
	ui_buttons->addFlag(STYLEFLAG_OUTLINE);
	ui_account->addFlag(STYLEFLAG_OUTLINE);
	ui_window->addFlag(STYLEFLAG_OUTLINE);

	/* Set onClick actions */
	ui_cancel->setAction(cancel);
}


/*
*	Handles mouse input
*/
static void mouseInput(int key, int state, int x, int y) {
	if (key == GLUT_LEFT_BUTTON && windowActive) {
		/* The following piece of code iterates over all the nodes in "ui_menu" object
		and checks if they're within given X,Y coordinates. */

		/* get nodes of all panels */
		std::vector<UI_Node*>& nodes1 = ui_buttons->getNodes();
		std::vector<UI_Node*>& nodes2 = ui_window->getNodes();
		std::vector<UI_Node*>& nodes3 = ui_account->getNodes();

		std::vector<UI_Node*> nodes;
		nodes.reserve(nodes1.size() + nodes2.size());
		nodes.insert(nodes.end(), nodes1.begin(), nodes1.end());
		nodes.insert(nodes.end(), nodes2.begin(), nodes2.end());
		nodes.insert(nodes.end(), nodes3.begin(), nodes3.end());
		/* iterate over said nodes */
		for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
			/* check if the clicked area is within node's coordinates */
			if (withinCoords(x, y, *i)) {
				if ((*i)->getName() == "Button") {
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
					}
				} else if ((*i)->getName() == "Checkbox") {

					/* checkbox event handling*/
					UI_Checkbox * chk = dynamic_cast<UI_Checkbox*>(*i); //dynamic cast node->checkbox
					if (chk != nullptr) { //if cast was successfull (meaning this indeed is a button)
						if (state == GLUT_DOWN) { //if mouseDown
							chk->setState(BTN_DOWN);
						}
						else if (chk->getState() == BTN_DOWN) { //if mouse released
							chk->setState(BTN_ACTIVE);
							chk->toggle();
						}
					}
				} else if ((*i)->getName() == "RadioButton") {
	
					/* checkbox event handling*/
					UI_RadioButton * chk = dynamic_cast<UI_RadioButton*>(*i); //dynamic cast node->checkbox
					if (chk != nullptr) { //if cast was successfull (meaning this indeed is a button)
						if (state == GLUT_DOWN) { //if mouseDown
							chk->setState(BTN_DOWN);
						}
						else if (chk->getState() == BTN_DOWN) { //if mouse released
							chk->setState(BTN_ACTIVE);
							chk->check();
							if (lastRadioButton != nullptr) {
								lastRadioButton->unCheck();
							}
							lastRadioButton = chk;
						}
					} /* Insert any other GUI elements handling under this comment */
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
	if (windowActive) {
		/* Get nodes of all panels */
		std::vector<UI_Node*>& nodes1 = ui_buttons->getNodes();
		std::vector<UI_Node*>& nodes2 = ui_window->getNodes();
		std::vector<UI_Node*>& nodes3 = ui_account->getNodes();

		std::vector<UI_Node*> nodes;
		nodes.reserve(nodes1.size() + nodes2.size());
		nodes.insert(nodes.end(), nodes1.begin(), nodes1.end());
		nodes.insert(nodes.end(), nodes2.begin(), nodes2.end());
		nodes.insert(nodes.end(), nodes3.begin(), nodes3.end());
		/* Iterate over nodes */
		for (std::vector<UI_Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i) {
			if ((*i)->getName() == "Button") {
				/* Button cast */
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
			} else if ((*i)->getName() == "Checkbox") {
				/* Checkbox cast */
				UI_Checkbox * chk = dynamic_cast<UI_Checkbox*>(*i);
				if (chk != nullptr) {
					if (withinCoords(x, y, *i)) {
						chk->setState(BTN_HOVER);
					}
					else {
						if (chk->getState() != BTN_DISABLED) {
							chk->setState(BTN_ACTIVE);
						}
					}
				}
			} else if ((*i)->getName() == "RadioButton") {
				/* Checkbox cast */
				UI_RadioButton * chk = dynamic_cast<UI_RadioButton*>(*i);
				if (chk != nullptr) {
					if (withinCoords(x, y, *i)) {
						chk->setState(BTN_HOVER);
					}
					else {
						if (chk->getState() != BTN_DISABLED) {
							chk->setState(BTN_ACTIVE);
						}
					}
				}
			}
		}
		glutPostRedisplay();
	}
}

/*
*	Go back to main menu
*/
static void cancel() {
	title::show();
}