#pragma once
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void enterDev(int argc, char** argv);
void printMsg(int type, std::string message);
void devLoop(int argc, char** argv);
void runCommand(std::string cmd, int argc, char** argv);
void getArguments(std::string cmd, std::string *arguments);

void cmd_title(int argc, char** argv);
void cmd_argst(std::string *arguments);
void cmd_help();