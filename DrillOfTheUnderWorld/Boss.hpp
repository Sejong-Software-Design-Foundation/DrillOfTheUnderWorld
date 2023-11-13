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

    // ���� ������ �ʿ� ������
    int curPosX = imageLayer.images[0].x;
    int curPosY = imageLayer.images[0].y;

    double angle = atan2(curPosY - y, curPosX - x);

    // �̵��� �Ÿ��� ���
    double dx = SPEED * cos(angle);
    double dy = SPEED * sin(angle);

    if (collisionCheck(x + dx, y + dy)) { return; }

    // BOSS ��ǥ�� ������Ʈ
    imageLayer.images[imageidx].x += dx;
    imageLayer.images[imageidx].y += dy;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}

void Boss::attack() {
    setCurrentCurPos(0, 0);
    printf("BOSS attacking PC!\n");

    // ���� ����
    // PC.HP -= attack_damage;
    // hp -= PC.attack_damage;

    // ������ ��
    if (NPCDead()) {
        return;
    }
}

#endif