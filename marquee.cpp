#include "marquee.h"
#include "console_utils.h"
#include <iostream>

Marquee::Marquee(const std::string &text)
    : text(text), x(0), y(5), dx(1), dy(1) {}

void Marquee::update(int maxX, int maxY)
{
    // check for horizontal collisions (left and right edges)
    if (x + text.length() >= maxX || x <= 0) {
        dx = -dx; // reverse horizontal direction
    }
    
    // check for vertical collisions (top and bottom edges)
    // we use y <= 3 to avoid overlapping with the header (which occupies rows 0-2)
    if (y >= maxY - 1 || y <= 3) {
        dy = -dy; // reverse vertical direction
    }

    // update position
    x += dx;
    y += dy;
    
    // ensure we don't get stuck at edges
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + text.length() >= maxX) x = maxX - text.length() - 1;
    if (y >= maxY) y = maxY - 1;
}

void Marquee::draw() const
{
    gotoxy(x, y);
    std::cout << text;
}