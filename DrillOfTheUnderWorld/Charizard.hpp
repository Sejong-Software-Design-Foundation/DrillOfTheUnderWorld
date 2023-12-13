#ifndef __CHARIZARD_
#define __CHARIZARD_

#define CHARIZARD_SPEED 12

#include "NPC.hpp"
#include "CharizardFireball.hpp"
#include <list>

using namespace std;

/// <summary>
/// === Charizard INFO ===
/// HP : 200
/// AD : 0 (ATTACK BY FIREBALLS)
/// MOVEMENT : NPCPATTERNMOVEMENT
/// </summary>

class Charizard : public NPC {
public:
	int movecnt;
	int phase;
	int iconIndex;

	list<CharizardFireball> fireballs;

public:
	Charizard(int x, int y);

	void checkFireballs();
	void move();
	void attack();

	void NPCHit(int atkLev);
	void AfterDead();
	void updateHPBar();
	void ultimate();
	void setPhase2();
};

Charizard::Charizard(int x, int y) : NPC(x, y, 200, 0, 1) {
	movecnt = 0;
	phase = 1;
	// Charizard image save
	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameCharizard, x, y, CHARIZARD_SCALE };

	// Charizard HP BAR image save
	char* curBossHPName = bmpBossHPName;
	if (maxHP > 100) curBossHPName = bmpBossHP_2Name;
	for (int i = 0; i < 100; i++) {
		imageArray[imageLayer.imageCount++] = { curBossHPName, AREA_ORIGIN_X + BLOCKSIZE + BOSS_HP_BAR_WIDTH * i, AREA_ORIGIN_Y - BLOCKSIZE, 1 };
		imageArray[imageLayer.imageCount - 1].isHide = true;
	}

	// Charizard HP BAR ICON save
	iconIndex = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameCharizard, AREA_ORIGIN_X, AREA_ORIGIN_Y - BLOCKSIZE,1 };
	imageArray[iconIndex].isHide = true;
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
	if (movecnt % 15 == 0) {
		fireballs.push_back(CharizardFireball(x, y));
	}
	else if (movecnt == 101) {
		if (phase == 2) ultimate();
		movecnt = 0;
	}
	else {
		if (movecnt % 4 == 0)NPCBossMovement(CHARIZARD_SPEED);
	}
}

void Charizard::attack() {
	list<CharizardFireball>::iterator it;
	for (it = fireballs.begin(); it != fireballs.end(); it++) {
		(*it).move();
	}
}

void Charizard::NPCHit(int atkLev) {
	NPC::NPCHit(atkLev);
	updateHPBar();

	char bmpNameHit[] = "CharizardHit.bmp";
	char bmpNameHitPhase2[] = "Charizard_Evolve2_Hit.bmp";
	if (phase == 1) imageArray[imageidx].fileName = bmpNameHit;
	else if (phase == 2) imageArray[imageidx].fileName = bmpNameHitPhase2;
	else imageArray[imageidx].fileName = bmpNameHit;

	imageLayer.renderAll(&imageLayer);
	if (phase == 1) imageArray[imageidx].fileName = bmpNameCharizard;
	else if (phase == 2) imageArray[imageidx].fileName = bmpNameCharizardEvolve2;
	else imageArray[imageidx].fileName = bmpNameCharizard;
	imageLayer.renderAll(&imageLayer);
	if (this->hp <= 100 && phase == 1) setPhase2();
}

void Charizard::AfterDead() {
	if (strcmp(imageArray[imageidx].fileName, bmpNameNull) == 0) return;

	list<CharizardFireball>::iterator it;
	for (it = fireballs.begin(); it != fireballs.end(); ) {
		imageArray[it->imageidx].fileName = bmpNameNull;
		it++;
	}
	fireballs.clear();
	char bmpNameHit[] = "Charizard_Evolve2_Hit.bmp";
	imageArray[imageidx].fileName = bmpNameHit;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	for (int i = 0; i < 15; i++) {
		imageArray[imageidx].fileName = bmpExplodeName[i % 5];
		imageArray[imageidx].scale = CHARIZARD_SCALE;
		imageLayer.renderAll(&imageLayer);
		Sleep(20);
	}
	imageArray[imageidx].fileName = bmpNameNull;
	imageLayer.renderAll(&imageLayer);
}

void Charizard::updateHPBar() {
	for (int i = maxHP; i > hp; i--) {
		if ((i - 1) / 100 == 1) {
			//if(strcmp(imageArray[imageidx + i % 100].fileName, bmpBossHPName) != 0) //100~199이면 빨간색으로 대치
			imageArray[imageidx + (i - 1) % 100 + 1].fileName = bmpBossHPName;
		}
		else {
			//if(strcmp(imageArray[imageidx + i % 100].fileName, bmpNameNull) != 0)
			imageArray[imageidx + (i - 1) % 100 + 1].fileName = bmpNameNull;
		}
		//0~99이면 nullBMP
	}
}

void Charizard::ultimate() {
	int curPosX = imageLayer.images[0].x;
	int curPosY = imageLayer.images[0].y;

	double angle = 45 * 3.14 / 180;
	double magnitude = 50;
	double new_angle = atan2(curPosY - y, curPosX - x) - angle;

	for (int i = 0; i < 2; i++) {
		fireballs.push_back(CharizardFireball(x, y));
		fireballs.back().dx = magnitude * cos(new_angle);
		fireballs.back().dy = magnitude * sin(new_angle);

		fireballs.back().movingtime = 20;

		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				fireballs.back().fireground[a][b] = 0;
			}
		}
		fireballs.back().fireground[1][1] = 1;
		imageLayer.images[fireballs.back().imageidx].fileName = bmpNameFireground;

		new_angle += angle * 2;
	}
}

void Charizard::setPhase2() {
	stopBGM();
	playBGM(bgmCharizardEvolve);

	phase = 2;
	imageArray[imageidx].fileName = bmpNameCharizardEvolve2;
	imageArray[imageidx].scale = 1;
	char bmpStart1[] = "redBackground.bmp";
	imageArray[imageLayer.imageCount++] = { bmpStart1, 0, 0, 1 };
	for (int i = 0; i < 3; i++) {
		imageArray[imageidx].fileName = bmpNameCharizard;
		imageArray[imageidx].scale = CHARIZARD_SCALE;
		imageArray[imageLayer.imageCount - 1].isHide = 1;
		imageLayer.renderAll(&imageLayer);
		Sleep(300);
		imageArray[imageidx].fileName = bmpNameCharizardEvolve2;
		imageArray[imageidx].scale = 1;
		imageArray[imageLayer.imageCount - 1].isHide = 0;
		imageLayer.renderAll(&imageLayer);
		Sleep(650);
	}

	imageArray[imageLayer.imageCount - 1].isHide = 0;
	imageLayer.imageCount--;
	imageArray[imageidx].fileName = bmpNameCharizardEvolve2;
	imageArray[imageidx].scale = 1;
	//getEvolvedCharizardArea();

	strcpy(bmpBedrockName, bmpBlueBedrockName);
	imageArray[iconIndex].fileName = bmpNameCharizardEvolve2;
	imageArray[iconIndex].scale = 0.25;
	imageLayer.renderAll(&imageLayer);

	// ready for PHASE2 AREA
	list<CharizardFireball>::iterator it;
	for (it = fireballs.begin(); it != fireballs.end(); it++) {
		(*it).eraseFireground();
	}
	fireballs.clear();

	strcpy(bmpNameFireball, bmpNameFireball_Blue);
	strcpy(bmpNameFireground, bmpNameFireground_Blue);

	movecnt = 100;
}

#endif