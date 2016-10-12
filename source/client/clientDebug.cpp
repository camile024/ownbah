/*
CLIENT DEBUGGING MODULE
Author: Kamil
*/
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>

//message types
#define MSG_NORMAL	0
#define	MSG_ERROR	1
#define	MSG_LOG		2
#define	MSG_NETWORK	3

//main dev function, called in main.cpp
void enterDev() {
		printMsg(MSG_NORMAL, "Entered development state.");
		devLoop();
		printMsg(MSG_NORMAL, "Closing down");
		exit(0);
}

//devLoop allows for using commands to make events occur
void devLoop() {
	std::string cmd = "";
	while (cmd != "quit" && cmd != "q" && cmd != "exit") {
		std::cin >> cmd;
		runCommand(cmd);
	}
}

//runs commands (switch statement only works with integral types, thus I had to use nested if statements. Keeping em in one function makes things clearer
void runCommand(std::string cmd) {
	if (cmd == "help") {
		cmd_help();
	}
}

//prints messages, useful for debugging, can be called in main.cpp
void printMsg(int type, std::string message) {
	switch (type) {
	case MSG_ERROR:
		std::cout << "[ERR] ";
		break;
	case MSG_LOG:
		std::cout << "[LOG] ";
		break;
	case MSG_NETWORK:
		std::cout << "[NET] ";
		break;
	default:
		break;
	}
	std::cout << message << std::endl;
}

/*

======================================================
== PUT ALL THE COMMAND FUNCTIONS BELOW THIS COMMENT ==
======================================================

*/
void cmd_help() {
	printMsg(MSG_NORMAL, "Available commands: ");
}

