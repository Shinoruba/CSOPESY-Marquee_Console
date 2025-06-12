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

int main()
{
    Marquee marquee("Hello world in marquee!");
    const int refreshDelay = 100; // ms
    const int pollDelay = 10;

    int frameCounter = 0;

    int cols, rows;
    getConsoleSize(cols, rows);

    while (true) {
        clearScreen();

        // Step 1: Print the fixed banner
        printHeader();
        std::cout << "\n[Press Q to quit]" << std::endl;
        marquee.draw();

        // Step 2: Display the marquee scroll
        //std::cout << marquee.getVisibleText() << std::endl;
        

        // Step 3: Update marquee on refresh tick
        if (frameCounter % (refreshDelay / pollDelay) == 0) {
            marquee.update(cols, rows);
        }

        // Step 4: Handle non-blocking quit
        if (keyPressed()) {
            char c = getChar();
            if (c == 'q' || c == 'Q') {
                std::cout << "\nExiting..." << std::endl;
                break;
            }
        }

        sleepMilliseconds(pollDelay);
        frameCounter++;
    }

    return 0;
}