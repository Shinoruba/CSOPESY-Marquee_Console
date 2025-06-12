#include "console_utils.h"
#include <windows.h>
#include <conio.h>

void clearScreen()
{
    system("cls");  // clear the console
}

void sleepMilliseconds(int ms)
{
    Sleep(ms);
}

bool keyPressed()
{
    return _kbhit();  // non-blocking check
}

char getChar()
{
    return _getch();  // read one character without waiting for Enter
}
