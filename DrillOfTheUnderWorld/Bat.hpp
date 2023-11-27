#ifndef __BAT_
#define __BAT_

#include "NPC.hpp"

/// <summary>
/// === BAT INFO ===
/// HP : 10
/// AD : 5
/// MOVEMENT : NPCPATTERNMOVEMENT
/// </summary>

class Bat : public NPC {

public:
    Bat(int x, int y);

    void move();
    void attack();
};

Bat::Bat(int x, int y) : NPC(x, y, 10, 5, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameBat, x, y, 1 };
}

void Bat::move() {
    NPCPatternMovement();
}

void Bat::attack() {
    pc.setHP(pc.getHP() - attack_damage);
}

#endif