/*
========================================================
MAIN CLIENT MODULE - THE RISK
Author: Kamil
========================================================
LIBRARIES USED: 
-GluT (freeglut 3.0.0) - creating windows, 
-OpenGL (glew 2.0.0) - all the drawing

I am using MS Visual Studio for all the work here, feel free to use
other IDE/OS, just make sure to get the libraries to make the project
compile on your machine

Ask me for help with libraries (they can be a pain to compile and get working)
I am creating my own GUI classes (gui.h/gui.cpp) based on glut
========================================================
*/

#pragma once

#include "main.h"
#include "title.h"

//game version
#define GAME_VER 0.1

//message types
#define MSG_NORMAL	0
#define	MSG_ERROR	1
#define	MSG_LOG		2
#define	MSG_NETWORK	3

//checks if dev argument is on, if it is, proceeds to dev stage where you can control the flow of the program
int main(int argc, char* argv[]) {
	bool debug = false;
	printMsg(MSG_NORMAL, "Application started...");
	debug = checkDebug(argc, argv);
	if (checkDev(argc, argv)) {
		enterDev(argc, argv);
	}
	printMsg(MSG_NORMAL, "Initialising game...");

	return 0;
}

//checks for debug argument
bool checkDebug(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		std::string arg(argv[i]);
		if (arg == "debug") {
			return true;
		}
	}
	return false;
}

//checks for development argument
bool checkDev(int argc,char* argv[]) {
	for (int i = 0; i < argc; i++) {
		std::string arg(argv[i]);
		if (arg == "dev") {
			return true;
		}
	}
	return false;
}

