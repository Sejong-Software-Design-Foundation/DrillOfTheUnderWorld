#ifndef __RAWK_HAWK_
#define __RAWK_HAWK_

#define RAWKHAWK_NORMAL_SPEED 48
#define RAWKHAWK_TRACK_SPEED 100

#include "NPC.hpp"

/// <summary>
/// === RawkHawk INFO ===
/// HP : 100
/// AD : 30
/// MOVEMENT : NPCPATTERNMOVEMENT && NPCTRACKINGMOVEMENT
/// </summary>

class RawkHawk : public NPC {
public:
    int movecnt;

public:
    RawkHawk(int x, int y);

    void move();
    void attack();

    void NPCHit(int atkLev);
    void AfterDead();
    void updateHPBar();
};

RawkHawk::RawkHawk(int x, int y) : NPC(x, y, 100, 30, 1) {
    movecnt = 0;
    maxHP = hp;

    // RawkHawk image save
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameRawkHawk, x, y, RAWKHAWK_SCALE };

    // RawkHawk HP BAR image save
    for (int i = 0; i < maxHP; i++) {
        imageArray[imageLayer.imageCount++] = { bmpBossHPName, AREA_ORIGIN_X + BLOCKSIZE + BOSS_HP_BAR_WIDTH * i, AREA_ORIGIN_Y - BLOCKSIZE, 1 };
        imageArray[imageLayer.imageCount - 1].isHide = true;
    }

    // RawkHawk HP BAR ICON save
    imageArray[imageLayer.imageCount++] = { bmpNameRawkHawk, AREA_ORIGIN_X, AREA_ORIGIN_Y - BLOCKSIZE,1 };
    imageArray[imageLayer.imageCount - 1].isHide = true;
}

void RawkHawk::move() {

    // 0-5 : 6sec
    if (cnt < 6) {
        NPCPatternMovement(RAWKHAWK_NORMAL_SPEED);
    }
    // 6-8 : 3sec
    else if (cnt < 9) {
        imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, RAWKHAWK_SCALE };
    }
    // 9-14 : 6sec
    else if (cnt < 15) {
        imageArray[imageidx] = { bmpNameRawkHawk_digging, x, y, RAWKHAWK_SCALE };
        NPCTrackingMovement(RAWKHAWK_TRACK_SPEED);
    }
    // 15-17 : 3sec
    else if (cnt < 18) {
        imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, RAWKHAWK_SCALE };
    }
    else if (cnt == 19) {
        imageArray[imageidx] = { bmpNameRawkHawk, x, y,RAWKHAWK_SCALE };
        cnt = -1;
    }

    cnt++;
}

void RawkHawk::attack() {
    int damage = attack_damage;

    if (pc.getHasThronCrown()) {
        damage *= 2;
    }
    pc.setHP(pc.getHP() - damage);
}

void RawkHawk::NPCHit(int atkLev) {
    // if RawkHawk is digging he's not attackable
    if (imageArray[imageidx].fileName == bmpNameRawkHawk_digging) return;

    NPC::NPCHit(atkLev);
    this->updateHPBar();
    char bmpNameHit[] = "RawkHawkHit.bmp";
    imageArray[imageidx].fileName = bmpNameHit;
    imageLayer.renderAll(&imageLayer);
    imageArray[imageidx].fileName = bmpNameRawkHawk;
    imageLayer.renderAll(&imageLayer);

}

void RawkHawk::AfterDead() {
    if (strcmp(imageArray[imageidx].fileName, bmpNameNull) == 0) return;

    char bmpNameHit[] = "RawkHawkHit.bmp";
    imageArray[imageidx].fileName = bmpNameHit;
    imageLayer.renderAll(&imageLayer);
    Sleep(1000);
    for (int i = 0; i < 15; i++) {
        imageArray[imageidx].fileName = bmpExplodeName[i % 5];
        imageArray[imageidx].scale = RAWKHAWK_SCALE;
        imageLayer.renderAll(&imageLayer);
    }
    imageArray[imageidx].fileName = bmpNameNull;
    imageLayer.renderAll(&imageLayer);
}

void RawkHawk::updateHPBar() {
    for (int i = 1; i <= maxHP; i++) {
        if (hp < i && strcmp(imageArray[imageidx + i].fileName, bmpNameNull) != 0) imageArray[imageidx + i].fileName = bmpNameNull;
    }
}

#endif