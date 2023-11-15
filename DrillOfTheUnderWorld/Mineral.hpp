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

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < 10; i++) {
        while (1) {
            x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
            y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

            int infoX = convertPosToInfoX(x);
            int infoY = convertPosToInfoY(y);

            int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

            if (blockInfo[infoY][infoX] == 2) {
                // 4�� �ؾ� �� �� �ֵ���
                blockInfo[infoY][infoX] = 6;
                // filename�� �ٲ��ֱ�
                imageLayer.images[imageIndex].fileName = bmpNameMineral;
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