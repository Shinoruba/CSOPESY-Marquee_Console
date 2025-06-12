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
    Marquee(const std::string &text);
    void update(int maxX, int maxY);
    void draw() const;
};

#endif