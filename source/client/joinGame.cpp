/*

JOIN GAME WINDOW
Author: Kamil

*/

#include "joinGame.h"

/*
*
*	WINDOW GLOBALS
*
*/
static UI_Textbox* selTextbox; //currently selected textbox
static bool windowActive = true;

static int windowSizeX = JOINGAME_WINDOW_SIZE_X;
static int windowSizeY = JOINGAME_WINDOW_SIZE_Y;
static float scaleX = JOINGAME_WINDOW_SCALE_X;
static float scaleY = JOINGAME_WINDOW_SCALE_Y;

static UI_Panel *ui_main; //main panel - it's not big anyway
static UI_Button *ui_serverbrowser; //serverbrowser button
static UI_Button *ui_connect; //connect by ip button
static UI_Button *ui_back; //back button
static UI_Textbox *ui_ip; //field to type in ip
static UI_Textbox *ui_port; //field to type in port
static UI_Label *ui_lab_ip; //IP label

static const int MIN_WINDOW_WIDTH = 350;
static const int MIN_WINDOW_HEIGHT = 220;
static const int MAX_WINDOW_WIDTH = 350;
static const int MAX_WINDOW_HEIGHT = 220;

/*
*	==========================
*	==========================
*	== NON-STATIC FUNCTIONS ==
*	==========================
*	==========================
*/

namespace joinGame {
	/*
	*	Shows the window
	*/
	void show() {
		glutSetWindowTitle("The Risk");
		windowSizeX = JOINGAME_WINDOW_SIZE_X;
		windowSizeY = JOINGAME_WINDOW_SIZE_Y;
		glutReshapeWindow(windowSizeX, windowSizeY);
		init();
		glutKeyboardFunc(keyboardInput);
		glutDisplayFunc(display);
		glutMouseFunc(mouseInput);
		glutPassiveMotionFunc(mouseMove);
		display();
	}

	/*
	*	Frees memory of all the UI objects (static globals with 'ui_' prefix)
	*/
	void freeUI() {
		delete ui_main;
		delete ui_serverbrowser;
		delete ui_connect;
		delete ui_back;
		delete ui_ip;
		delete ui_port;
		delete ui_lab_ip;
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
	bool windowChanged = false;
	/*Resize resolution-adjusted items*/
	/*	Get current window sizes and change them accordingly
	If window sizes have changed, make sure to resize them
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
	if (windowChanged) {
		scaleX = JOINGAME_WINDOW_SCALE_X;
		scaleY = JOINGAME_WINDOW_SCALE_Y;
		ui_main->setSizes(0, 0, windowSizeX, windowSizeY);
		ui_serverbrowser->setSizes(scaleX * 3, 10, scaleX * 15 + 5, 30);
		ui_lab_ip->setSizes(scaleX * 1, 50);
		ui_ip->setSizes(scaleX * 3, 50, scaleX * 11, 30);
		ui_port->setSizes(scaleX * 14 + 5, 50, scaleX * 4, 30);
		ui_connect->setSizes(scaleX * 5, 90, scaleX * 11, 30);
		ui_back->setSizes(scaleX * 5, 130, scaleX * 11, 30);
	}

	/*Do the actual drawing*/
	ui_main->setColorRGB(255, 193, 100, 100);
	ui_main->draw();
	glutSwapBuffers();
}

/*
*	Initialising Options
*	Author: Kamil
*/
static void init() {
	glClearColor(0.0f / 255, 0.0f / 255, 0.0f / 255, 0.0);
	joinGame::freeUI(); //Free memory of UI items in case they already exist
					   /* Window Settings */
	ui_main = new UI_Panel(0, 0, windowSizeX, windowSizeY);
	ui_serverbrowser = new UI_Button(*ui_main, scaleX * 5, 10, scaleX * 10, 30, "Server Browser");
	ui_lab_ip = new UI_Label(*ui_main, scaleX * 1, 50, "IP: ");
	ui_ip = new UI_Textbox(*ui_main, scaleX * 3, 50, scaleX * 12, 30);
	ui_port = new UI_Textbox(*ui_main, scaleX * 15 + 5, 50, scaleX * 4, 30);
	ui_connect = new UI_Button(*ui_main, scaleX * 5, 90, scaleX * 10, 30, "Connect by IP");
	ui_back = new UI_Button(*ui_main, scaleX * 5, 130, scaleX * 10, 30, "Back");
	/* Styles */
	//ui_window->setStyle(STYLE_NORMAL);
	ui_ip->setMaxLength(16);
	ui_port->setMaxLength(5);
	/* Set onClick actions */
	ui_back->setAction(cancel);
}

/*
*	Handles mouse input
*/	
static void mouseInput(int key, int state, int x, int y) {
	if (key == GLUT_LEFT_BUTTON && windowActive) {
		if(selTextbox != nullptr)
			selTextbox->deselect();
		/* The following piece of code iterates over all the nodes in "ui_menu" object
		and checks if they're within given X,Y coordinates. */

		/* get nodes of all panels */
		std::vector<UI_Node*>& nodes1 = ui_main->getNodes();

		std::vector<UI_Node*> nodes;
		//nodes.reserve(nodes1.size()); //is really needed?
		nodes.insert(nodes.end(), nodes1.begin(), nodes1.end());
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
				 /* Insert any other GUI elements handling under this comment */
				} else if ((*i)->getName() == "Textbox") {
					UI_Textbox *txt = dynamic_cast<UI_Textbox*>(*i);
					if (txt != nullptr) {
						if (state == GLUT_DOWN) {
							txt->setState(BTN_DOWN);
						} else if (txt->getState() == BTN_DOWN) {
							txt->setState(BTN_ACTIVE);
							txt->select();
							selTextbox = txt;
						}
					}
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
		std::vector<UI_Node*>& nodes1 = ui_main->getNodes();


		std::vector<UI_Node*> nodes;
		nodes.reserve(nodes1.size());
		nodes.insert(nodes.end(), nodes1.begin(), nodes1.end());
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
			}
			else if ((*i)->getName() == "Textbox") {
				/* Textbox cast */
				UI_Textbox *txt = dynamic_cast<UI_Textbox*>(*i);
				if (txt != nullptr) {
					if (withinCoords(x, y, *i)) {
						txt->setState(BTN_HOVER);
					} else {
						if (txt->getState() != BTN_DISABLED) {
							txt->setState(BTN_ACTIVE);
						}
					}
				}
			}
		} 
		glutPostRedisplay();
	}
}

void keyboardInput(unsigned char key, int x, int y){
	if (selTextbox != nullptr) {
		switch (key) {
		case 8:
			selTextbox->removeChar();
			break;
		default:
			selTextbox->addChar(key);
			break;
		}
	}
	glutPostRedisplay(); /* this redraws the scene without
						 waiting for the display callback so that any changes appear
						 instantly */
}

/*
*	Go back to main menu
*/
static void cancel() {
	title::show();
}