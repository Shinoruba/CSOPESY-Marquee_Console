#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <string>

void clearScreen(); // clear the windows console
void sleepMilliseconds(int ms); // sleep for a number of milliseconds
bool keyPressed();  // check if a key was pressed (non-blocking)
char getChar(); // get the character that was pressed (must call after keyPressed)

#endif