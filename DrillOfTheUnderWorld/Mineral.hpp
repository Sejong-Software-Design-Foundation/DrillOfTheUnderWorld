#ifndef __Mineral_
#define __Mineral_

#include "NPC.hpp"

class Mineral : public NPC {

public:
    Mineral();

    void move(ImageLayer* il);
    void attack();
};

Mineral::Mineral() : NPC(0, 0, 0, 0, 1) {

    char bmpNameMineral[] = "Mineral.bmp";

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < 5; i++) {
        while (1) {
            x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 20);
            y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 20);

            if (blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] == 2) {
                imageArray[4 + convertPosToInfoY(y) * 25 + convertPosToInfoX(x)] = { bmpNameMineral, x,y,1 };
                break;
            }

        }
    }
}

void Mineral::move(ImageLayer* il) {
    // no movement for Mineral
    // just checking if PCisNear

    if (PCNear(imageLayer)) {
        attack();
        return;
    }
    return;
}

void Mineral::attack() {
    setCurrentCurPos(0, 0);
    printf("PC wants to Mineral!\n");
}

#endif