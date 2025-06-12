#include "marquee.h"

Marquee::Marquee(const std::string& text, size_t displayWidth)
    : message(text + "   "), offset(0), width(displayWidth) {
    // add spaces at end to create a smooth loop
}

void Marquee::update()
{
    offset = (offset + 1) % message.length();   // move the offset forward and wrap around
}

std::string Marquee::getVisibleText() const
{
    if(offset + width <= message.length())
    {
        return message.substr(offset, width);
    } 
    else
    {
        // if we need to wrap around the message
        size_t firstPart = message.length() - offset;
        return message.substr(offset, firstPart) + message.substr(0, width - firstPart);
    }
}