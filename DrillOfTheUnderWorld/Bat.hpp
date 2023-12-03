#ifndef __BAT_
#define __BAT_

#define BAT_SPEED 48

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
    void setNewPosition(int x, int y);
};

Bat::Bat(int x, int y) : NPC(x, y, 10, 5, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameBat, x, y, 1 };
}

void Bat::move() {
    NPCPatternMovement(BAT_SPEED);
}

void Bat::attack() {
    pc.setHP(pc.getHP() - attack_damage);
}
void Bat::setNewPosition(int x, int y) {
    imageLayer.images[imageidx].x = x;
    imageLayer.images[imageidx].y = y;
    this->x = x;
    this->y = y;
}

#endif