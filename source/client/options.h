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

static void init();
void optionsDisplay(void);
static void window();
void optionsCreate();
void freeOptionsUIObjects();