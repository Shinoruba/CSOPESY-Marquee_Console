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

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleSize(int &cols, int &rows)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}