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

#include "gui/UIMain.h"

//custom headers
#include "clientDebug.h"

//other windows
#include "options.h"
#include "joinGame.h"

namespace joinGame {
	void show(void);
	void freeUI(void);
}

static void display(void);
static void init(void);
static void settings();
static void mouseInput(int key, int state, int x, int y);
static void mouseMove(int x, int y);
void keyboardInput(unsigned char key, int x, int y);