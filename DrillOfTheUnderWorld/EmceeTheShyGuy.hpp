#ifndef __EMCEE_THE_SHY_GUY_
#define __EMCEE_THE_SHY_GUY_

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
	int movecnt;
	list<NPCBullet> bullets;

public:
	EmceeTheShyGuy(int x, int y);

	void checkBullets();
	void move();
	void attack();
	void setNewPosition(int x, int y);
};

EmceeTheShyGuy::EmceeTheShyGuy(int x, int y) : NPC(x, y, 0, 10, 1) {
	movecnt = 0;

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, x, y, 1 };
}

void EmceeTheShyGuy::checkBullets() {

	list<NPCBullet>::iterator it;

	for (it = bullets.begin(); it != bullets.end(); it++) {
		int bullet_idx = (*it).imageidx;
		if (imageArray[bullet_idx].fileName == bmpNameNull) {
			bullets.erase(it);
		}
	}
}

void EmceeTheShyGuy::move() {
	movecnt++;

	checkBullets();
	attack();

	// if moved 8 times shoot once and reset mvcnt
	if (movecnt == 8) {
		//bullets.push_back(NPCBullet(x, y));
		movecnt = 0;
	}
	else {
		NPCTrackingMovement();
		//NPCPatternMovement();
	}
}

// Emcee's attack is moving NPCBullets 
void EmceeTheShyGuy::attack() {
	list<NPCBullet>::iterator it;
	for (it = bullets.begin(); it != bullets.end(); it++) { (*it).move(); }
}

void EmceeTheShyGuy::setNewPosition(int x, int y) {
	imageLayer.images[imageidx].x = x;
	imageLayer.images[imageidx].y = y;
}

#endif