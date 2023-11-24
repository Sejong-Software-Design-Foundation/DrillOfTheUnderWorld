#ifndef __NPCBULLET_
#define __NPCBULLET_

#include "NPC.hpp"

/// <summary>
/// === NPCBULLET INFO ===
/// HP : 0
/// AD : 10
/// MOVEMENT : CONSTANT DIRECTION
/// </summary>

class NPCBullet : public NPC {
private:
	double dx, dy;

public:
	// starting pos(x,y)
	// direction(dx,dy);
	NPCBullet(int x, int y);

	void move();
	void attack();
};

NPCBullet::NPCBullet(int x, int y) : NPC(x, y, 0, 10, 1) {

	// 자신의 방향은 자신이 생성될때 계산해서 결정
	int curPosX = imageLayer.images[0].x;
	int curPosY = imageLayer.images[0].y;

	double angle = atan2(curPosY - y, curPosX - x);

	dx = 100 * cos(angle);
	dy = 100 * sin(angle);

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameFireball, x, y, 1 };
}

void NPCBullet::move() {

	if (PCNear()) {
		attack();
		imageLayer.images[imageidx].fileName = bmpNameNull;
	}

	if (collisionCheck(x + dx, y + dy)) {
		imageLayer.images[imageidx].fileName = bmpNameNull;
	}

	// update bullet position
	imageLayer.images[imageidx].x += dx;
	imageLayer.images[imageidx].y += dy;

	x = imageLayer.images[imageidx].x;
	y = imageLayer.images[imageidx].y;
}

void NPCBullet::attack() {
	pc.setHP(pc.getHP() - attack_damage);
}

#endif