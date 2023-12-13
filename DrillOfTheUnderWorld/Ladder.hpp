#ifndef __LADDER_
#define __LADDER_

#include "NPC.hpp"

class Ladder : public NPC {
private:
    int adamantiumIndex = 0;
    char bmpAdamantiumName[7][20] = { "adamantium1.bmp","adamantium2.bmp" ,"adamantium3.bmp" ,"adamantium4.bmp" ,"adamantium5.bmp", "adamantium6.bmp", "adamantium7.bmp" };

public:
    Ladder(int x, int y);

    void move();
    void attack();
    bool goSafety();
    bool goEnding();
    bool pcNearAdamantium();
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
    playSound(bgmClear);
    rewardUI();
}

bool Ladder::goEnding() {
    NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);

    imageArray[imageidx].fileName = bmpAdamantiumName[adamantiumIndex % 7];
    //imageLayer.renderAll(&imageLayer);
    adamantiumIndex++;
    if (pcNearAdamantium()) {
        return true;
    }
    return false;
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

bool Ladder::pcNearAdamantium() {
    int PC_X = convertPosToInfoX(imageLayer.images[0].x);
    int PC_Y = convertPosToInfoY(imageLayer.images[0].y);

    int NPC_Y = y;
    int NPC_X = x;

    // printf("(%d %d) (%d %d)", PC_X, PC_Y, NPC_X, NPC_Y);

    int startX = convertPosToInfoX(NPC_X);
    int startY = convertPosToInfoY(NPC_Y);

    for (int curY = startY; curY < startY + BLOCKSIZE * 5; curY++) {
        for (int curX = startX; curX < startX + BLOCKSIZE * 5; curX++) {
            for (int dy = 0; dy < BLOCKSIZE; dy++) {
                for (int dx = 0; dx < BLOCKSIZE; dx++) {
                    if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
                    if (curX == PC_X + dx && curY == PC_Y + dy) return true;
                }
            }
        }
    }
    return false;
}

#endif