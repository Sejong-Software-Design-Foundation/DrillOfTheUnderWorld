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
};

RawkHawk::RawkHawk(int x, int y) : NPC(x, y, 100, 30, 1) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameRawkHawk_pattern, x, y, 1 };
}

void RawkHawk::move() {
    cnt++;

    // 0-5 : 6sec
    if (cnt < 6) {
        NPCPatternMovement(RAWKHAWK_NORMAL_SPEED);
    }
    // 6-8 : 3sec
    else if (cnt < 9) {
        imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, 1 };
    }
    // 9-14 : 6sec
    else if (cnt < 15) {
        imageArray[imageidx] = { bmpNameRawkHawk_tracking, x, y, 1 };
        NPCTrackingMovement(RAWKHAWK_TRACK_SPEED);
    }
    // 15-17 : 3sec
    else if (cnt < 18) {
        imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, 1 };
    }
    else if (cnt == 19) {
        imageArray[imageidx] = { bmpNameRawkHawk_pattern, x, y,1 };
        cnt = 0;
    }
}

void RawkHawk::attack() {
    pc.setHP(pc.getHP() - attack_damage);
}

#endif