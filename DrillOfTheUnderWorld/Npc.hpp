#ifndef __NPC_
#define __NPC_

#include "common.hpp"

// abstract class
class NPC {
public:
    virtual void move() = 0;
    virtual void attack() = 0;

public:
    int dir[4][2] = { {1,0},{0,1},{-1,0}, {0,-1} };
    // ���� Console x, y��ǥ�� ��
    int x, y;
    // image array �� �ش� ��ü bmp�� idx ��ȣ
    int imageidx;

    int hp;
    int attack_damage;
    int curDirection;
    int cnt;

    NPC(int x, int y, int hp, int ad, int dir);
    //~NPC();

    bool NPCDead();
    bool PCNear(ImageLayer& imageLayer);

    void NPCPatternMovement();
    void NPCTrackingMovement();
};

NPC::NPC(int x, int y, int hp, int ad, int dir) {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->attack_damage = ad;
    // default�� ������ ������
    this->curDirection = 0;
    cnt = 0;
}

bool NPC::NPCDead() { return hp < 0 ? true : false; }

bool NPC::PCNear(ImageLayer& imageLayer) {
    // PC ��ǥ �ޱ�
    int PC_X = imageLayer.images[0].x;
    int PC_Y = imageLayer.images[0].y;

    int NPC_Y = y;
    int NPC_X = x;

    return (NPC_X == PC_X && NPC_Y >= PC_Y - BLOCKSIZE && NPC_Y <= PC_Y + BLOCKSIZE) ||
        (NPC_Y == PC_Y && NPC_X >= PC_X - BLOCKSIZE && NPC_X <= PC_X + BLOCKSIZE);

    /*
    return ((NPC_Y - BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y + BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y == PC_Y && NPC_X - BLOCKSIZE == PC_X) ||
        (NPC_Y == PC_Y && NPC_X + BLOCKSIZE == PC_X));
    */
}

void NPC::NPCPatternMovement() {
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

void NPC::NPCTrackingMovement() {
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

    // Mole ��ǥ�� ������Ʈ
    imageLayer.images[imageidx].x += dx;
    imageLayer.images[imageidx].y += dy;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}
#endif