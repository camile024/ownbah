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

//game version
#define GAME_VER 0.1

//message types
#define MSG_NORMAL	0
#define	MSG_ERROR	1
#define	MSG_LOG		2
#define	MSG_NETWORK	3

int main(int argc, char* argv[]);
bool checkDebug(int argc, char* argv[]);
bool checkDev(int argc, char* argv[]);