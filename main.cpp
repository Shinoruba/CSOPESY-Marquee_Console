// main.cpp
#include <iostream>
#include <string>
#include "marquee.h"
#include "console_utils.h"

void printHeader()
{
    std::string headerText = "* Displaying a marquee console! *";
    std::string border(headerText.length(), '*');

    gotoxy(0, 0);
    std::cout << border;
    gotoxy(0, 1);
    std::cout << headerText;
    gotoxy(0, 2);
    std::cout << border;
}

void printHelp(int cols)
{
    gotoxy(0, 3);
    std::cout << "Commands: [Q]uit [S]peed+ [D]own [H]elp";
    clearLine(4);  // Clear previous messages
}

int main()
{
    Marquee marquee("Hello world in marquee!", 2);  // initialized with speed=2 for faster movement
    const int refreshDelay = 100;   // How often to update animation
    const int pollDelay = 50;   // How often to check for input

    int frameCounter = 0;

    int cols, rows;
    getConsoleSize(cols, rows);

    
        // Clear screen and draw initial state
    clearScreen();
    printHeader();
    printHelp(cols);

    // Store previous position for clearing
    int prevX = marquee.getX();
    int prevY = marquee.getY();

    while (true) {
        // Clear previous position
        gotoxy(prevX, prevY);
        std::cout << std::string(marquee.getText().length(), ' ');

        // Update and draw
        marquee.update(cols, rows);
        marquee.draw();

        // Store current position for next clear
        prevX = marquee.getX();
        prevY = marquee.getY();

        // Handle input
        if (keyPressed()) {
            char c = tolower(getChar());
            switch(c) {
                case 'q':
                    gotoxy(0, rows - 1);
                    std::cout << "Exiting...";
                    return 0;
                case 's':
                    marquee.setSpeed(std::min(marquee.getSpeed() + 1, 5));
                    gotoxy(0, 4);
                    std::cout << "Speed: " << marquee.getSpeed();
                    break;
                case 'd':
                    marquee.setSpeed(std::max(marquee.getSpeed() - 1, 1));
                    gotoxy(0, 4);
                    std::cout << "Speed: " << marquee.getSpeed();
                    break;
                case 'h':
                    printHelp(cols);
                    break;
                default:
                    gotoxy(0, 4);
                    std::cout << "Unknown command. Type H for help.";
            }
        }

        sleepMilliseconds(pollDelay);
    }

    return 0;
}