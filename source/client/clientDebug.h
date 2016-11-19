#pragma once
//standard includes
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


#define MSG_NORMAL	0
#define	MSG_ERROR	1
#define	MSG_LOG		2
#define	MSG_NETWORK	3

void enterDev(int argc, char** argv);
void printMsg(int type, std::string message);
void devLoop();
void runCommand(std::string cmd);
void getArguments(std::string cmd, std::string *arguments);

void cmd_title();
void cmd_argst(std::string *arguments);
void cmd_help();