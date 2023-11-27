#ifndef __LADDER_
#define __LADDER_

#include "NPC.hpp"

class Ladder : public NPC {

public:
    Ladder(int x, int y);

    void move();
    void attack();
    void setNewPosition(int x, int y);
};

Ladder::Ladder(int x, int y) : NPC(x, y, 0, 0, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameLadder, x, y, 1 };
}

void Ladder::move() {
    if (PCNear())
    {
        attack();
    }
}

void Ladder::attack() {
    isOnArea = false;
    isOnReward = true;
}
void Ladder::setNewPosition(int x, int y) {
    imageLayer.images[imageidx].x = x;
    imageLayer.images[imageidx].y = y;
    this->x = x;
    this->y = y;
}

#endif