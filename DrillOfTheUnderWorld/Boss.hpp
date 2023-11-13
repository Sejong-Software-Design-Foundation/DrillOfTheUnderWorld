#ifndef __BOSS_
#define __BOSS_

#include "NPC.hpp"

class Boss : public NPC {
public:
    Boss(int x, int y);

    void move(ImageLayer* il);
    void attack();
};

Boss::Boss(int x, int y) : NPC(x, y, 100, 50, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameBoss, x, y, 1 };
}

void Boss::move(ImageLayer* il) {
    if (PCNear(imageLayer)) {
        attack();
        return;
    }

    // 추적 움직임 필요 데이터
    int curPosX = imageLayer.images[0].x;
    int curPosY = imageLayer.images[0].y;

    double angle = atan2(curPosY - y, curPosX - x);

    // 이동할 거리를 계산
    double dx = SPEED * cos(angle);
    double dy = SPEED * sin(angle);

    if (collisionCheck(x + dx, y + dy)) { return; }

    // BOSS 좌표를 업데이트
    imageLayer.images[imageidx].x += dx;
    imageLayer.images[imageidx].y += dy;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}

void Boss::attack() {
    setCurrentCurPos(0, 0);
    printf("BOSS attacking PC!\n");

    // 서로 공격
    // PC.HP -= attack_damage;
    // hp -= PC.attack_damage;

    // 죽으면 끝
    if (NPCDead()) {
        return;
    }
}

#endif