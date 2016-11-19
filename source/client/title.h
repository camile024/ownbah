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
#include "gui/gui.h"

//custom headers
#include "clientDebug.h"

static void titleDisplay(void);
static void init(void);
static void window();
void titleCreate();
static void options();
static void login();
void exit();
bool withinCoords(int x, int y, UI_Node* a);
void freeTitleUIObjects();
static void mouseInput(int key, int state, int x, int y);
static void mouseMove(int x, int y);