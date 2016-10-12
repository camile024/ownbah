/*
MAIN CLIENT MODULE
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

//custom headers
#include "clientDebug.h"
#include "main.h"
#include "title.h"

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
		if (arg == "dev4431") {
			return true;
		}
	}
	return false;
}

