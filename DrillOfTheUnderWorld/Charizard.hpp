#ifndef __CHARIZARD_
#define __CHARIZARD_

#define CHARIZARD_SPEED 20

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
	// if movecnt is 8 shoot bullet
	int movecnt;
	list<CharizardFireball> fireballs;

public:
	Charizard(int x, int y);

	void checkFireballs();
	void move();
	void attack();
};

Charizard::Charizard(int x, int y) : NPC(x, y, 0, 10, 1) {
	movecnt = 0;

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameCharizard, x, y, 1 };
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

#endif