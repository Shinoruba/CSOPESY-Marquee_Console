// main.cpp
#include <iostream>
#include <string>
#include <sstream>
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

// void printHelp(int cols)
// {
//     gotoxy(0, 3);
//     std::cout << "Commands: [ESC]Quit [1]Speed+ [2]Down- [3]Help";
//     //clearLine(4);
//     std::cout << std::string(cols - 42, ' ');   // added some padding spaces to ensure the line is fully written
// }

void printInputPrompt(int rows, int cols)
{
    gotoxy(0, rows - 2);
    std::cout << "Enter a command for MARQUEE_CONSOLE: ";
    std::cout << std::string(cols - 35, ' ');   // clear rest of line
}

void printCommandResult(const std::string& command, int rows, int cols)
{
    gotoxy(0, rows - 1);
    // clears the entire line first
    std::cout << std::string(cols, ' ');
    gotoxy(0, rows - 1);
    std::cout << "  Command processed in MARQUEE_CONSOLE: " << command;
}

void updateInputDisplay(const std::string& inputBuffer, int rows, int cols)
{
    // Clear the input line and redraw it
    gotoxy(0, rows - 2);
    std::cout << std::string(cols, ' '); // Clear the entire line
    gotoxy(0, rows - 2);
    std::cout << "Enter a command for MARQUEE_CONSOLE: " << inputBuffer;
    // Position cursor at the end of input
    gotoxy(35 + inputBuffer.length(), rows - 2);
}

// void redrawStaticElements(int cols, int rows)
// {
//     // Redraw header
//     printHeader();
//     // Redraw commands
//     printHelp(cols);
// }

int main()
{
    Marquee marquee("Hello world in marquee!", 2);  // initialized with speed=2 for faster movement
    const int refreshDelay = 100;   // How often to update animation
    const int pollDelay = 50;   // How often to check for input

    int cols, rows;
    getConsoleSize(cols, rows);

    
    // Clear screen and draw initial state
    clearScreen();
    printHeader();
    // printHelp(cols);
    printInputPrompt(rows, cols);

    // Store previous position for clearing
    int prevX = marquee.getX();
    int prevY = marquee.getY();
    std::string inputBuffer = "";
    // bool waitingForInput = false;
    // int frameCounter = 0;

    while (true) {
        // Clear previous position
        gotoxy(prevX, prevY);
        std::cout << std::string(marquee.getText().length(), ' ');

        // Update and draw
        marquee.update(cols, rows - 3); // Reserve space for input area

        // Check if marquee will interfere with command line
        // if (marquee.getY() == 3) {
        //     // Redraw the command line if marquee is on it
        //     printHelp(cols);
        // }

        marquee.draw();

        // Store current position for next clear
        prevX = marquee.getX();
        prevY = marquee.getY();

        // Periodically redraw static elements to prevent corruption
        // frameCounter++;
        // if (frameCounter % 50 == 0) { // Every ~2.5 seconds at 50ms delay
        //     redrawStaticElements(cols, rows);
        //     printInputPrompt(rows, cols);
        //     if (!inputBuffer.empty()) {
        //         updateInputDisplay(inputBuffer, rows, cols);
        //     }
        // }

        // Handle input
        if (keyPressed()) {
            char c = getChar();
            
            if (c == 27) { // ESC key
                gotoxy(0, rows - 1);
                std::cout << "Exiting...";
                return 0;
            }
            else if (c == '\r' || c == '\n') { // Enter key
                if (!inputBuffer.empty()) {
                    // Process command - display whatever was typed
                    printCommandResult(inputBuffer, rows, cols);
                    inputBuffer.clear();
                    printInputPrompt(rows, cols);
                    // Position cursor after the prompt
                    gotoxy(35, rows - 2);
                }
            }
            else if (c == '\b' || c == 127) { // Backspace
                if (!inputBuffer.empty()) {
                    inputBuffer.pop_back();
                    updateInputDisplay(inputBuffer, rows, cols);
                }
            }
            else if (c >= 32 && c <= 126) { // Printable characters
                inputBuffer += c;
                updateInputDisplay(inputBuffer, rows, cols);
            }
        }

        sleepMilliseconds(pollDelay);
    }

    return 0;
}