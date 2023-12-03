#ifndef __MOLE_
#define __MOLE_

#define MOLE_SPEED 48

#include "NPC.hpp"

/// <summary>
/// === MOLE INFO ===
/// HP : 50
/// AD : 15
/// MOVEMENT : NPCPATTERNMOVEMENT
/// </summary>

class Mole : public NPC {
public:
    Mole(int x, int y);

    void move();
    void attack();
};

Mole::Mole(int x, int y) : NPC(x, y, 50, 15, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameMole, x, y, 1 };
}

void Mole::move() {
    NPCPatternMovement(MOLE_SPEED);
}

void Mole::attack() {
    pc.setHP(pc.getHP() - attack_damage);
}

#endif