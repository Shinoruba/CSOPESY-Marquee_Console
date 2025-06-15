#include "marquee.h"
#include "console_utils.h"
#include <iostream>
#include <algorithm>

Marquee::Marquee(const std::string &text, int speed)
    : text(text), x(5), y(5), dx(1), dy(1), speed(speed) {}

void Marquee::update(int maxX, int maxY)
{
    x += dx * speed;
    y += dy * speed;

    if(x <= 0) {
        x = 0;
        dx = abs(dx);
    }
    else if(x + text.length() >= maxX) {
        x = maxX - text.length() - 1;
        dx = -abs(dx);
    }

    if(y <= 3) {
        y = 3;
        dy = abs(dy);
    }
    else if(y >= maxY - 1) {
        y = maxY - 1;
        dy = -abs(dy);
    }

    x = std::max(0, std::min(x, maxX - (int)text.length() - 1));
    y = std::max(3, std::min(y, maxY - 1));
}

void Marquee::draw() const
{
    gotoxy(x, y);
    std::cout << text;
}