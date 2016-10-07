/*
MAIN SERVER SOURCE
Author: Kamil
*/
#define STATE_INVALID	-1
#define STATE_SETUP		0
#define STATE_WARMUP	1
#define STATE_GAME		2
#define STATE_FINISH	3
#define STATE_EXIT		4

#include <iostream>
#include <exception>
#include "main.h"
#include "stdlib.h"

//settings variables - hardcoded for now
int g_turn_hours = 0;
int g_turn_minutes = 0;
int g_turn_seconds = 1;

//state of the game
int g_state = STATE_INVALID;


//initialise, load settings
int main() {
	g_state = STATE_SETUP;
	int turn_hours = 0;
	int turn_minutes = 0;
	int turn_seconds = 1;
	try {
		std::cout << "Server initialised.\n";
		std::cout << "Loading settings from file...\n";
		loadSettings();
		std::cout << "Loading rules from file...\n";
		loadRules();
	}
	catch (std::exception x) {
		std::cout << x.what();
		shutDown();
	}
	std::cout << "Settings loaded succesfully.\n";
	g_state = STATE_WARMUP;
	gameLoop();
	return 0;
}

void gameLoop() { //tba
	while (g_state != STATE_EXIT) {
		g_state = STATE_EXIT;
	}
	std::cout << "Game has finished.\n";
	system("pause");
	void shutDown();
}

void loadRules() throw(std::exception) { //tba
	//throw std::exception("Failed to load rules!\n");
}

void shutDown() {
	saveLogs();
	exit(0);
}

void saveLogs() {
	return;
}
void loadSettings() { //tba
	return;
}
