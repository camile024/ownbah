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
#include "title.h"

namespace options {
	void show();
	void freeUI();
}

static void init();
static void display(void);
static void mouseInput(int key, int state, int x, int y);
static void mouseMove(int x, int y);
static void cancel(void);