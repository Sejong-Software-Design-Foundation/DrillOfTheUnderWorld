#ifndef __ZOMBIE_
#define __ZOMBIE_

#include "NPC.hpp"

class Zombie : public NPC {

public:
    Zombie(int x, int y);

    void move(ImageLayer* il);
    void attack();
};

Zombie::Zombie(int x, int y) : NPC(x, y, 100, 50, 1) {

    int infoX = convertPosToInfoX(x);
    int infoY = convertPosToInfoY(y);

    int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;
    // render 출력을 위한 image 번호 저장
    // image에 객체 이미지 추가
    this->imageidx = imageIndex;
    imageLayer.images[imageIndex].fileName = bmpZombieName;

}

void Zombie::move(ImageLayer* il) {

    if (PCNear(imageLayer)) {
        attack();
        return;
    }

    cnt++;

    srand(static_cast<unsigned int>(time(nullptr)));

    if (cnt == 3) {
        curDirection = rand() % 4;
        cnt = 0;
    }

    if (collisionCheck(imageLayer.images[imageidx].x + dir[curDirection][0] * BLOCKSIZE, imageLayer.images[imageidx].y + dir[curDirection][1] * BLOCKSIZE)) {
        curDirection = rand() % 4;
        cnt = 0;
        return;
    }

    imageLayer.images[imageidx].x += dir[curDirection][0] * BLOCKSIZE;
    imageLayer.images[imageidx].y += dir[curDirection][1] * BLOCKSIZE;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}

void Zombie::attack() {

    setCurrentCurPos(0, 0);
    printf("NPC attacking PC!\n");
}

#endif __ZOMBIE_