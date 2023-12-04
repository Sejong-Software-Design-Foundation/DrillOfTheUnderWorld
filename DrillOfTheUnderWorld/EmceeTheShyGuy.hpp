#ifndef __EMCEE_THE_SHY_GUY_
#define __EMCEE_THE_SHY_GUY_

#define EMCEE_THESHYGUY_SPEED 48
#define ULTIMATE_BULLET_NUM 10

#include "NPC.hpp"
#include "NPCBullet.hpp"
#include <list>

using namespace std;

/// <summary>
/// === EMCEETHESHYGUY INFO ===
/// HP : 100
/// AD : 20
/// MOVEMENT : NPCPATTERNMOVEMENT
/// </summary>

class EmceeTheShyGuy : public NPC {
public:
	// if movecnt is 8 shoot bullet
	int movecnt;
	list<NPCBullet> bullets;

public:
	EmceeTheShyGuy(int x, int y);

	void checkBullets();
	void move();
	void attack();

	void ultimate();
};

EmceeTheShyGuy::EmceeTheShyGuy(int x, int y) : NPC(x, y, 0, 10, 1) {
	movecnt = 0;

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, x, y, 1 };
}

void EmceeTheShyGuy::checkBullets() {

	list<NPCBullet>::iterator it;

	for (it = bullets.begin(); it != bullets.end(); ) {
		int bullet_idx = (*it).imageidx;
		if (imageArray[bullet_idx].fileName == bmpNameNull) {
			it = bullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void EmceeTheShyGuy::move() {
	movecnt++;
	checkBullets();
	attack();

	//printf("%d", movecnt);
	// if moved 8 times shoot once and reset mvcnt
	if (movecnt % 5 == 0) {
		bullets.push_back(NPCBullet(x, y));
	}
	else if (movecnt == 19) {
		ultimate();
		movecnt = 0;
	}
	else {
		NPCBossMovement(EMCEE_THESHYGUY_SPEED);
	}
}

// Emcee's attack is moving NPCBullets 
void EmceeTheShyGuy::attack() {
	list<NPCBullet>::iterator it;
	for (it = bullets.begin(); it != bullets.end(); it++) { (*it).move(); }
}

void EmceeTheShyGuy::ultimate() {
	int curPosX = imageLayer.images[0].x;
	int curPosY = imageLayer.images[0].y;

	double angle = 360 / ULTIMATE_BULLET_NUM;
	double magnitude = 100;
	double new_angle = atan2(curPosY - y, curPosX - x);

	for (int i = 0; i < ULTIMATE_BULLET_NUM; i++) {
		bullets.push_back(NPCBullet(x, y));
		bullets.back().dx = magnitude * cos(new_angle);
		bullets.back().dy = magnitude * sin(new_angle);

		new_angle += angle;
	}
}

#endif