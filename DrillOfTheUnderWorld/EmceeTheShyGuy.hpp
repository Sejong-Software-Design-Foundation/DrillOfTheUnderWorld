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
	// if movecnt is 8 shoot bullet
	int movecnt;
	list<NPCBullet> bullets;

public:
	EmceeTheShyGuy(int x, int y);

	void checkBullets();
	void move();
	void attack();
	void NPCHit(int AtkLev);
	void AfterDead();
};

EmceeTheShyGuy::EmceeTheShyGuy(int x, int y) : NPC(x, y, 3, 10, 1) {
	movecnt = 0;

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, x, y, BOSS_SCALE };
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
	if (movecnt == 8) {
		if (rand()%2 == 0) bullets.push_back(NPCBullet(x, y+BLOCKSIZE*BOSS_SCALE/2));
		else bullets.push_back(NPCBullet(x + BLOCKSIZE*BOSS_SCALE - 16, y + BLOCKSIZE * BOSS_SCALE / 2));
		movecnt = 0;
	}
	else {
		NPCBossMovement();
		//NPCTrackingMovement();
		//NPCPatternMovement();
	}
}

// Emcee's attack is moving NPCBullets 
void EmceeTheShyGuy::attack() {
	//pc.setHP(pc.getHP() - 10);
	list<NPCBullet>::iterator it;
	for (it = bullets.begin(); it != bullets.end(); it++) { (*it).move(); }
}

void EmceeTheShyGuy::NPCHit(int AtkLev) {
	NPC::NPCHit(AtkLev);
	char bmpNameHit[] = "EmceeTheShyGuyHit.bmp";
	imageArray[imageidx].fileName = bmpNameHit;
	imageLayer.renderAll(&imageLayer);
	imageArray[imageidx].fileName = bmpNameEmceeTheShyGuy;
	imageLayer.renderAll(&imageLayer);
}

void EmceeTheShyGuy::AfterDead() {
	if (strcmp(imageArray[imageidx].fileName, bmpNameNull) == 0) return;
	list<NPCBullet>::iterator it;
	for (it = bullets.begin(); it != bullets.end(); ) {
		imageArray[it->imageidx].fileName = bmpNameNull;
		it++;
	}
	bullets.clear();
	char bmpNameHit[] = "EmceeTheShyGuyHit.bmp";
	imageArray[imageidx].fileName = bmpNameHit;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	for (int i = 0;i < 15;i++) {
		imageArray[imageidx].fileName = bmpExplodeName[i%5];
		imageArray[imageidx].scale = BOSS_SCALE;
		imageLayer.renderAll(&imageLayer);
	}
	imageArray[imageidx].fileName = bmpNameNull;
	imageLayer.renderAll(&imageLayer);
}

#endif