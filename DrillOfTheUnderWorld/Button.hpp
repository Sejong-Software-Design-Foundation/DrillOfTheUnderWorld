#pragma once
#ifndef __BUTTON__
#define __BUTTON__

#include "NPC.hpp"

class Button : public NPC {
private:
    int buttonNumber;
    bool isPressed;

public:
    Button(int buttonNumbe);

    void move();
    void attack();
    void setNewPosition(int x, int y);
    void setIsPressed(bool isPressed);
    bool getIsPressed();
};

Button::Button(int buttonNumber) : NPC(0, 0, 0, 0, 1) {
    this->buttonNumber = buttonNumber;
    isPressed = false;
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameLadder, 0, 0, 1 };
}

void Button::move() {
    if (PCNear())
    {
        attack();
    }
}

void Button::attack() {
    if (!isPressed) {
        isPressed = true;
        buttonPressedOrderList.push_back(buttonNumber);
    }
}
void Button::setNewPosition(int x, int y) {
    imageLayer.images[imageidx].x = x;
    imageLayer.images[imageidx].y = y;
    this->x = x;
    this->y = y;
}

void Button::setIsPressed(bool isPressed) {
    this->isPressed = isPressed;
}

bool Button::getIsPressed() {
    return this->isPressed;
}
#endif