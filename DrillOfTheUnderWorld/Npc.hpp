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
    // 실제 Console x, y좌표가 들어감
    int x, y;
    // image array 내 해당 객체 bmp의 idx 번호
    int imageidx;

    int hp;
    int attack_damage;
    int curDirection;
    int cnt;

    NPC(int x, int y, int hp, int ad, int dir);
    //~NPC();

    bool NPCDead();
    bool PCNear();

    void NPCPatternMovement();
    void NPCTrackingMovement();
};

NPC::NPC(int x, int y, int hp, int ad, int dir) {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->attack_damage = ad;
    // default가 오른쪽 움직임
    this->curDirection = 0;
    cnt = 0;
}

bool NPC::NPCDead() { return hp < 0 ? true : false; }

bool NPC::PCNear() {
    // PC 좌표 받기
    int PC_X = convertPosToInfoX(imageLayer.images[0].x);
    int PC_Y = convertPosToInfoY(imageLayer.images[0].y);

    int NPC_Y = y;
    int NPC_X = x;

   // printf("(%d %d) (%d %d)", PC_X, PC_Y, NPC_X, NPC_Y);

    int startX = convertPosToInfoX(NPC_X);
    int startY = convertPosToInfoY(NPC_Y);

    for (int curY = startY; curY < startY + BLOCKSIZE; curY++) {
        for (int curX = startX; curX < startX + BLOCKSIZE; curX++) {
            for (int dy = 0; dy < BLOCKSIZE; dy++) {
                for (int dx = 0;dx < BLOCKSIZE;dx++) {
                    if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
                    if (curX == PC_X + dx && curY == PC_Y + dy) { 
                        pc.setHP(pc.getHP() - 1);
                        return true; 
                    }
                }
            }
        }
    }
    return false;/*
    if (NPC_X - BLOCKSIZE <= PC_X && PC_X <= NPC_X + BLOCKSIZE
        && NPC_Y - BLOCKSIZE <= PC_Y && PC_Y <= NPC_Y + BLOCKSIZE) return true;
    return false;*/

    /*return (NPC_X == PC_X && NPC_Y >= PC_Y - BLOCKSIZE && NPC_Y <= PC_Y + BLOCKSIZE) ||
        (NPC_Y == PC_Y && NPC_X >= PC_X - BLOCKSIZE && NPC_X <= PC_X + BLOCKSIZE);*/

    
    /*return ((NPC_Y - BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y + BLOCKSIZE == PC_Y && NPC_X == PC_X) ||
        (NPC_Y == PC_Y && NPC_X - BLOCKSIZE == PC_X) ||
        (NPC_Y == PC_Y && NPC_X + BLOCKSIZE == PC_X));*/
    
}

void NPC::NPCPatternMovement() {
    if (PCNear()) {
        attack();
        return;
    }

    cnt++;

    //srand(static_cast<unsigned int>(time(nullptr)));

    if (cnt == 3) {
        curDirection = rand() % 4;
        cnt = 0;
    }

    if (collisionCheck(imageLayer.images[imageidx].x + dir[curDirection][0] * SPEED, imageLayer.images[imageidx].y + dir[curDirection][1] * SPEED)) {
        curDirection = rand() % 4;
        cnt = 0;
        return;
    }

    imageLayer.images[imageidx].x += dir[curDirection][0] * SPEED;
    imageLayer.images[imageidx].y += dir[curDirection][1] * SPEED;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}

void NPC::NPCTrackingMovement() {
    if (PCNear()) {
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

    // Mole 좌표를 업데이트
    imageLayer.images[imageidx].x += dx;
    imageLayer.images[imageidx].y += dy;

    x = imageLayer.images[imageidx].x;
    y = imageLayer.images[imageidx].y;
}
#endif