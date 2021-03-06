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

namespace title {
	void create();
	void show(void);
	void freeUI(void);
}
void exit();

static void display(void);
static void init(void);
static void settings();
static void window(void);
static void login();
static void mouseInput(int key, int state, int x, int y);
static void mouseMove(int x, int y);
