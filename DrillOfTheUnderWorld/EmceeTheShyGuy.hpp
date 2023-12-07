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
	void attack() ;
	void ultimate();
	void NPCHit(int atkLev);
	void AfterDead();
	void updateHPBar();
	int getMaxHP();
};

EmceeTheShyGuy::EmceeTheShyGuy(int x, int y) : NPC(x, y, 50, 10, 1) {
	movecnt = 0;
	maxHP = hp;

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, x, y, EMCEE_SCALE };
	for (int i = 0;i < maxHP;i++) {
		imageArray[imageLayer.imageCount++] = { bmpBossHPName,AREA_ORIGIN_X + BLOCKSIZE + BOSS_HP_BAR_WIDTH*i,AREA_ORIGIN_Y - BLOCKSIZE,1};
		imageArray[imageLayer.imageCount - 1].isHide = true;
	}
	imageArray[imageLayer.imageCount++] = { bmpNameEmceeTheShyGuy, AREA_ORIGIN_X, AREA_ORIGIN_Y - BLOCKSIZE,1 };
	imageArray[imageLayer.imageCount - 1].isHide = true;
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
    if (rand()%2 == 0) bullets.push_back(NPCBullet(x, y+BLOCKSIZE*EMCEE_SCALE/2));
		else bullets.push_back(NPCBullet(x + BLOCKSIZE*EMCEE_SCALE - 16, y + BLOCKSIZE * EMCEE_SCALE / 2));
		//bullets.push_back(NPCBullet(x, y));
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
	//pc.setHP(pc.getHP() - 10);
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
void EmceeTheShyGuy::NPCHit(int atkLev) {
	NPC::NPCHit(atkLev);
	updateHPBar();
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
	playSound(bgmExplosion);
	Sleep(1000);
	for (int i = 0;i < 15;i++) {
		imageArray[imageidx].fileName = bmpExplodeName[i%5];
		imageArray[imageidx].scale = EMCEE_SCALE;
		imageLayer.renderAll(&imageLayer);
	}
	for (int i = imageidx; i <= imageidx + maxHP + 1;i++) {
		imageArray[i].isHide = true;
	}
	imageArray[imageidx].fileName = bmpNameNull;
	imageLayer.renderAll(&imageLayer);
}

void EmceeTheShyGuy::updateHPBar() {
	for (int i = 1;i <= maxHP;i++) {
		if (hp < i && strcmp(imageArray[imageidx + i].fileName, bmpNameNull) != 0) imageArray[imageidx + i].fileName = bmpNameNull;
	}
}

#endif