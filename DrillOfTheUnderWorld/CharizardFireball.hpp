#ifndef __CHARIZARD_FIREBALL_
#define __CHARIZARD_FIREBALL_

#define FIREGROUND_SEC 30

#include "NPC.hpp"
#include <vector>

using namespace std;

/// <summary>
/// === CharizardFireball INFO ===
/// HP : 0
/// AD : 20
/// MOVEMENT : CONSTANT DIRECTION
/// </summary>

class CharizardFireball : public NPC {
public:
	double dx, dy;
	int movingtime;
	int fireground[3][3];

	// vector for fireground image indexs
	vector<int> fireground_indexs;

public:
	// starting pos(x,y)
	// direction(dx,dy);
	CharizardFireball(int x, int y);

	bool PCNear();

	void move();
	void attack();

	void initFireground();
	void makeFireground();
	void eraseFireground();
};

CharizardFireball::CharizardFireball(int x, int y) : NPC(x, y, 0, 20, 1) {

	// fireball moves 5-10 sec
	movingtime = 5 + rand() % 5;
	initFireground();

	// initialize direction of the fireball
	int curPosX = imageLayer.images[0].x;
	int curPosY = imageLayer.images[0].y;

	double angle = atan2(curPosY - y, curPosX - x);

	dx = 80 * cos(angle);
	dy = 80 * sin(angle);

	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameFireball, x, y, 1 };
}

// check if PC is on Fireground of each Fireball
bool CharizardFireball::PCNear() {
	int PC_X = convertPosToInfoX(imageLayer.images[0].x);
	int PC_Y = convertPosToInfoY(imageLayer.images[0].y);

	int FIREGROUND_Y = y - BLOCKSIZE;
	int FIREGROUND_X = x - BLOCKSIZE;

	// first fireground index from 9 square area
	int startX = convertPosToInfoX(FIREGROUND_X);
	int startY = convertPosToInfoY(FIREGROUND_Y);

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (fireground[i][k] == 1) {
				for (int curY = startY + BLOCKSIZE * i; curY < startY + BLOCKSIZE; curY++) {
					for (int curX = startX + BLOCKSIZE * k; curX < startX + BLOCKSIZE; curX++) {
						for (int dy = 0; dy < BLOCKSIZE; dy++) {
							for (int dx = 0; dx < BLOCKSIZE; dx++) {
								if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
								if (curX == PC_X + dx && curY == PC_Y + dy) return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

// this lives until eraseFireground
void CharizardFireball::move() {

	if (PCNear()) {
		attack();
	}

	if (collisionCheck(x + dx, y + dy)) {
		cnt = movingtime;
	}

	if (cnt < movingtime) {
		// update bullet position
		imageLayer.images[imageidx].x += dx;
		imageLayer.images[imageidx].y += dy;

		x = imageLayer.images[imageidx].x;
		y = imageLayer.images[imageidx].y;
	}
	else if (cnt == movingtime) {
		makeFireground();
	}
	else if (cnt > movingtime + FIREGROUND_SEC) {
		eraseFireground();
	}

	cnt++;
}

void CharizardFireball::attack() {
	pc.setHP(pc.getHP() - attack_damage);
}

void CharizardFireball::initFireground() {
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			fireground[i][k] = rand() % 2;
		}
	}
	fireground[1][1] = 1;
}

void CharizardFireball::makeFireground() {

	int startX = x - BLOCKSIZE;
	int startY = y - BLOCKSIZE;

	int infoX = convertPosToInfoX(startX);
	int infoY = convertPosToInfoY(startY);

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (blockInfo[startY + BLOCKSIZE * i][startX + BLOCKSIZE * k] == 0)
				if (fireground[i][k]) {
					fireground_indexs.push_back(imageLayer.imageCount);
					imageArray[imageLayer.imageCount++] = { bmpNameFireground, startX + BLOCKSIZE * i, startY + BLOCKSIZE * k, 1 };
				}
		}
	}
	// always change the ceneter image to fireground image
	imageArray[imageidx].fileName = bmpNameFireground;
}

void CharizardFireball::eraseFireground() {

	for (int i = 0; i < fireground_indexs.size(); i++) {
		imageArray[fireground_indexs[i]].fileName = bmpNameNull;
	}

	// this code is for Charizard checkBullets erase finished fireground
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			fireground[i][k] = 0;
		}
	}

	imageArray[imageidx].fileName = bmpNameNull;
}

#endif