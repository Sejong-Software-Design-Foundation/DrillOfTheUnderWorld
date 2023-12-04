#ifndef __LADDER_
#define __LADDER_

#include "NPC.hpp"

class Ladder : public NPC {

public:
    Ladder(int x, int y);

    void move();
    void attack();
    bool goSafety();
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
    if (isFlagArea && pc.getFlagCnt() < 3) return;
    rewardUI();
}

bool Ladder::goSafety() {
    if (PCNear())
    {
        stageLevel++;
        visitSafety();
        if (stageLevel >= 4) {
            //TODO
            return true;
        }
        return true;
    }
    return false;
}

#endif