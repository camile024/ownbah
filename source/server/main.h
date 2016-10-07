#pragma once
#include <exception>
void loadRules() throw(std::exception);
void gameLoop();
void loadSettings();
void shutDown();
void saveLogs();
