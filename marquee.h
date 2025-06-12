#ifndef MARQUEE_H
#define MARQUEE_H

#pragma once
#include <string>

class Marquee {
private:
    std::string text;
    int x, y;
    int dx, dy; // direction deltas
    int speed;      // movement speed multiplier

public:
    Marquee(const std::string &text, int speed = 2);
    void update(int maxX, int maxY);
    void draw() const;
    std::string getText() const { return text; }
    int getSpeed() const { return speed; }
    void setSpeed(int newSpeed) { speed = newSpeed; }
    int getX() const { return x; }
    int getY() const { return y; }
};

#endif