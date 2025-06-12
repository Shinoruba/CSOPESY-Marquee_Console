#ifndef MARQUEE_H
#define MARQUEE_H

#include <string>

class Marquee {
private:
    std::string message;  // full marquee text
    size_t offset;        // current scroll offset
    size_t width;         // visible width in characters

public:
    Marquee(const std::string& text, size_t displayWidth);

    void update();  // scroll the message by one position
    
    std::string getVisibleText() const; // get the current visible part of the message
};

#endif