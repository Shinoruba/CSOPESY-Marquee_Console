#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
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

void printInputPrompt(int rows, int cols)
{
    gotoxy(0, rows - 2);
    std::cout << "Enter a command for MARQUEE_CONSOLE: ";
    std::cout << std::string(cols - 35, ' ');
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
    gotoxy(0, rows - 2);
    std::cout << std::string(cols, ' ');
    gotoxy(0, rows - 2);
    std::cout << "Enter a command for MARQUEE_CONSOLE: " << inputBuffer;
    gotoxy(35 + inputBuffer.length(), rows - 2);
}

// ==================================================================================
int main()
{
    Marquee marquee("Hello world in marquee!", 2);
    const int refreshDelay = 40;   // How often to update animation
    const int pollDelay = 15;   // How often to check for input

    /*
    const int refreshDelay = 50;   
    const int pollDelay = 50;
        standard/default speed for marquee string and text responsiveness

    const int refreshDelay = 25;   
    const int pollDelay = 50;
        marquee string bounces around faster than previous test

    const int refreshDelay = 250;
    const int pollDelay = 50;  
        marquee string moves slow, and it's "hopping" around, instead of having a flowy feel when its bouncing around

    const int refreshDelay = 50;
    const int pollDelay = 5; 
        text is extremely responsive, compared to previous tests

    const int refreshDelay = 50;  
    const int pollDelay = 250;
        text is extremely UNRESPONSIVE, compared to previous test

    const int refreshDelay = 40;  
    const int pollDelay = 15;
        PERFECT BALANCE

    */ 

    int cols, rows;
    getConsoleSize(cols, rows);

    
    // Clear screen and draw initial state
    clearScreen();
    printHeader();
    printInputPrompt(rows, cols);

    // Store previous position for clearing
    int prevX = marquee.getX();
    int prevY = marquee.getY();
    std::string inputBuffer = "";

    auto lastRefresh = std::chrono::steady_clock::now();
    auto lastPoll = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        
        // Update animation only at refresh rate
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRefresh).count() >= refreshDelay) {
            gotoxy(prevX, prevY);
            std::cout << std::string(marquee.getText().length(), ' ');

            marquee.update(cols, rows - 3);
            marquee.draw();

            prevX = marquee.getX();
            prevY = marquee.getY();
            
            lastRefresh = now;
        }

        // Check input only at polling rate
        if(std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPoll).count() >= pollDelay) {
            if(keyPressed()) {
                char c = getChar();
                
                if(c == 27) {
                    gotoxy(0, rows - 1);
                    std::cout << "Exiting...";
                    return 0;
                }
                else if(c == '\r' || c == '\n') {
                    if (!inputBuffer.empty()) {
                        printCommandResult(inputBuffer, rows, cols);
                        inputBuffer.clear();
                        printInputPrompt(rows, cols);
                        gotoxy(35, rows - 2);
                    }
                }
                else if(c == '\b' || c == 127) {
                    if (!inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        updateInputDisplay(inputBuffer, rows, cols);
                    }
                }
                else if(c >= 32 && c <= 126) {
                    inputBuffer += c;
                    updateInputDisplay(inputBuffer, rows, cols);
                }
            }
            
            lastPoll = now;
        }

        sleepMilliseconds(1);
    }

    return 0;
}