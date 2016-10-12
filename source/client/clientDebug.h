#pragma once
#include <iostream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void enterDev();
void printMsg(int type, std::string message);
void devLoop();
void runCommand(std::string cmd);
void cmd_help();