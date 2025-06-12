// main.cpp
#include <iostream>
#include <string>
#include "marquee.h"
#include "console_utils.h"

void printHeader() {
    std::string headerText = "* Displaying a marquee console! *";
    std::string border(headerText.length(), '*');

    std::cout << border << std::endl;
    std::cout << headerText << std::endl;
    std::cout << border << std::endl << std::endl;
}

int main() {
    const std::string text = "Hello world in marquee!";
    const size_t displayWidth = 40;

    Marquee marquee(text, displayWidth);

    const int refreshDelay = 100; // in ms
    const int pollDelay = 10;     // check for key press every 10ms

    int frameCounter = 0;

    while (true) {
        clearScreen();

        // Step 1: Print the fixed banner
        printHeader();

        // Step 2: Display the marquee scroll
        std::cout << marquee.getVisibleText() << std::endl;
        std::cout << "\n[Press Q to quit]" << std::endl;

        // Step 3: Update marquee on refresh tick
        if (frameCounter % (refreshDelay / pollDelay) == 0) {
            marquee.update();
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