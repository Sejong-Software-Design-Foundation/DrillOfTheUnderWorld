#ifndef __NPC_
#define __NPC_

#include "common.hpp"

// abstract class
class NPC {
public:
    virtual void move(ImageLayer* imageLayer) = 0;
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

bool NPC::NPCDead() {
    return hp < 0 ? true : false;
}

bool NPC::PCNear(ImageLayer& imageLayer) {
    // PC ��ǥ �ޱ�
    int PC_X = imageLayer.images[0].x;
    int PC_Y = imageLayer.images[0].y;

    int NPC_Y = y;
    int NPC_X = x;

    return ((NPC_Y - BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y + BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y == PC_Y && NPC_X - BLOCKSIZE == PC_X) ||
        (NPC_Y == PC_Y && NPC_X + BLOCKSIZE == PC_X));
}

#endif