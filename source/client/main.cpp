/*
MAIN CLIENT MODULE
Author: Kamil
*/
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "clientDebug.h"
#include "main.h"
#include "title.h"

//checks if dev argument is on, if it is, proceeds to dev stage where you can control the flow of the program
int main(int argv, char** args) {
	bool debug = false;
	debug = checkDebug(argv, args);
	if (checkDev(argv, args)) {
		enterDev();
	}
	return 0;
}

//checks for debug argument
bool checkDebug(int argv, char** args) {
	for (int i = 0; i < argv; i++) {
		if (args[i] == "debug") {
			return true;
		}
	}
}

//checks for development argument
bool checkDev(int argv,char** args) {
	for (int i = 0; i < argv; i++) {
		if (args[i] == "dev4431") {
			return true;
		}
	}
}

