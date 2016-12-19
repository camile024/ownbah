/*
CLIENT DEBUGGING MODULE
Author: Kamil
*/
#pragma once

#include "title.h"
#include "options.h"
#include "clientDebug.h"

//message types
#define MSG_NORMAL	0
#define	MSG_ERROR	1
#define	MSG_LOG		2
#define	MSG_NETWORK	3

//main dev function, called in main.cpp
void enterDev(int argc, char** argv) {
		printMsg(MSG_NORMAL, "Entered development mode.");
		devLoop();
		printMsg(MSG_NORMAL, "Closing down");
		exit(0);
}

//devLoop allows for using commands to make events occur
void devLoop() {
	std::string cmd = "";
	while (cmd != "quit" && cmd != "q" && cmd != "exit") {
		getline(std::cin, cmd);
		runCommand(cmd);
	}
}

//runs commands (switch statement only works with integral types, thus I had to use if statements. Keeping em in one function makes things clearer
void runCommand(std::string cmd) {
	std::string arguments[10];
	getArguments(cmd, arguments);
	cmd = arguments[0];
	if (cmd == "help") { cmd_help(); }
	else if (cmd == "argst") { cmd_argst(arguments); }
	else if (cmd == "title") { cmd_title(); }
}

//separates all the words (up to 10) into a string array (including the command itself)
void getArguments(std::string cmd, std::string *arguments) {
	int j = 0;
	arguments[0] = "";
	for (unsigned int i = 0; i < cmd.length(); i++) {
		if (cmd[i] == ' ' && j < 10) {
			j++;
			arguments[j] = "";
		} else {
			arguments[j] += cmd[i];
		}
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
	printMsg(MSG_NORMAL, "Available commands: quit, q, exit, title, argst");
}

void cmd_title() {
	title::create();
}

void cmd_argst(std::string *arguments) {
	printMsg(MSG_LOG, arguments[1]);
}

