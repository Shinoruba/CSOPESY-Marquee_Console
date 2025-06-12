#include "marquee.h"
#include "console_utils.h"
#include <iostream>

Marquee::Marquee(const std::string &text)
    : text(text), x(0), y(5), dx(1), dy(1) {}

void Marquee::update(int maxX, int maxY)
{
    // bounce off walls
    if (x + text.length() >= maxX || x <= 0) dx = -dx;
    if (y >= maxY - 1 || y <= 4) dy = -dy; // avoid overlapping header

    x += dx;
    y += dy;
}

void Marquee::draw() const
{
    gotoxy(x, y);
    std::cout << text;
}