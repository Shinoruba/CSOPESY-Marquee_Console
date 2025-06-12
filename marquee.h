#ifndef MARQUEE_H
#define MARQUEE_H

#pragma once
#include <string>

class Marquee {
private:
    std::string text;
    size_t offset;        // current scroll offset
    size_t width;         // visible width in characters
    int x, y;
    int dx, dy; // direction deltas

public:
    Marquee(const std::string &text);

    void update(int maxX, int maxY);
    void draw() const;
    
    //std::string getVisibleText() const; // get the current visible part of the message
};

#endif