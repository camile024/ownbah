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

void display(void);
void init(void);
void window();
void titleCreate();
void doDrawing();
void login(int ID);
bool withinCoords(int x, int y, UI_Node* a);
void freeTitleUIObjects();
void mouseInput(int key, int state, int x, int y);