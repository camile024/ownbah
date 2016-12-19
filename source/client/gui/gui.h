#pragma once
//standard includes
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <vector>

//graphics
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GL\glut.h>

//custom headers
#include "gui_defines.h"
#include "../clientDebug.h"





bool reshapeWindow(int&, int&, int, int, int, int);
void drawString(void *font, std::string msg, float x, float y);







