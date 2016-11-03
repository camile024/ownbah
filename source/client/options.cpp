/*
OPTIONS SCREEN (settings)
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
*
*	WINDOW GLOBALS
*
*/
static int windowSizeX = GetSystemMetrics(SM_CXSCREEN) / 5;
static int windowSizeY = GetSystemMetrics(SM_CYSCREEN) / 4 + 200;
static UI_Panel *ui_settings; //settings panel
static UI_Panel *ui_window; //window settings panel
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