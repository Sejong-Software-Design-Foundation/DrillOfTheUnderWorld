#ifndef __CHARIZARD_
#define __CHARIZARD_

#define CHARIZARD_SPEED 30

#include "NPC.hpp"
#include "CharizardFireball.hpp"
#include <list>

using namespace std;

/// <summary>
/// === Charizard INFO ===
/// HP : 100
/// AD : 0 (ATTACK BY FIREBALLS)
/// MOVEMENT : NPCPATTERNMOVEMENT
/// </summary>

class Charizard : public NPC {
public:
    int movecnt;

    list<CharizardFireball> fireballs;

public:
    Charizard(int x, int y);

    void checkFireballs();
    void move();
    void attack();

    void NPCHit(int atkLev);
    void AfterDead();
    void updateHPBar();
};

Charizard::Charizard(int x, int y) : NPC(x, y, 100, 0, 1) {
    movecnt = 0;

    // Charizard image save
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameCharizard, x, y, CHARIZARD_SCALE };

    // Charizard HP BAR image save
    for (int i = 0; i < maxHP; i++) {
        imageArray[imageLayer.imageCount++] = { bmpBossHPName, DEFAULT_LAYER_MARGIN_X + AREA_ORIGIN_X + BLOCKSIZE + BOSS_HP_BAR_WIDTH * i,AREA_ORIGIN_Y - BLOCKSIZE,1 };
        imageArray[imageLayer.imageCount - 1].isHide = true;
    }

    // Charizard HP BAR ICON save
    imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, DEFAULT_LAYER_MARGIN_X + AREA_ORIGIN_X, AREA_ORIGIN_Y - BLOCKSIZE,1 };
    imageArray[imageLayer.imageCount - 1].isHide = true;
}

void Charizard::checkFireballs() {

    list<CharizardFireball>::iterator it;

    for (it = fireballs.begin(); it != fireballs.end(); ) {
        int fireball_idx = (*it).imageidx;
        if (imageArray[fireball_idx].fileName == bmpNameNull) {
            it = fireballs.erase(it);
        }
        else {
            it++;
        }
    }
}

void Charizard::move() {
    movecnt++;
    checkFireballs();

    attack();

    // if moved 10 times shoot once and reset mvcnt
    if (movecnt == 10) {
        fireballs.push_back(CharizardFireball(x, y));
        movecnt = 0;
    }
    else {
        NPCBossMovement(CHARIZARD_SPEED);
    }
}

void Charizard::attack() {
    list<CharizardFireball>::iterator it;
    for (it = fireballs.begin(); it != fireballs.end(); it++) {
        (*it).move();
    }
}

void Charizard::NPCHit(int atkLev) {
    NPC::NPCHit(atkLev);
    updateHPBar();

    char bmpNameHit[] = "CharizardHit.bmp";
    imageArray[imageidx].fileName = bmpNameHit;

    imageLayer.renderAll(&imageLayer);
    imageArray[imageidx].fileName = bmpNameEmceeTheShyGuy;
    imageLayer.renderAll(&imageLayer);
}

void Charizard::AfterDead() {
    if (strcmp(imageArray[imageidx].fileName, bmpNameNull) == 0) return;

    list<CharizardFireball>::iterator it;
    for (it = fireballs.begin(); it != fireballs.end(); ) {
        imageArray[it->imageidx].fileName = bmpNameNull;
        it++;
    }
    fireballs.clear();
    char bmpNameHit[] = "CharizardHit.bmp";
    imageArray[imageidx].fileName = bmpNameHit;
    imageLayer.renderAll(&imageLayer);
    Sleep(1000);
    for (int i = 0; i < 15; i++) {
        imageArray[imageidx].fileName = bmpExplodeName[i % 5];
        imageArray[imageidx].scale = CHARIZARD_SCALE;
        imageLayer.renderAll(&imageLayer);
    }
    imageArray[imageidx].fileName = bmpNameNull;
    imageLayer.renderAll(&imageLayer);
}

void Charizard::updateHPBar() {
    for (int i = 1; i <= maxHP; i++) {
        if (hp < i && strcmp(imageArray[imageidx + i].fileName, bmpNameNull) != 0) imageArray[imageidx + i].fileName = bmpNameNull;
    }
}

#endif