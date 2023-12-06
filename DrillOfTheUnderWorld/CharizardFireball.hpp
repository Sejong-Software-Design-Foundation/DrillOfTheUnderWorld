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
	bool fireground[3][3];

	// vector for fireground image indexs
	vector<int> fireground_indexes;

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
	int PC_X = imageLayer.images[0].x;
	int PC_Y = imageLayer.images[0].y;

	int startX = x - BLOCKSIZE;
	int startY = y - BLOCKSIZE;

	int curY, curX;

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			// if false dont check
			if (!fireground[i][k]) continue;

			curY = startY + BLOCKSIZE * i;
			curX = startX + BLOCKSIZE * k;

			if (PC_X >= curX && PC_X <= curX + BLOCKSIZE && PC_Y >= curY && PC_Y <= curY + BLOCKSIZE) {
				return true;
			}
		}
	}

	return false;
}

// this lives until eraseFireground
void CharizardFireball::move() {

	// check the 9 blocks of fireground area

	if (PCNear() && cnt >= movingtime && cnt <= movingtime + FIREGROUND_SEC) {
		attack();
	}

	if (cnt < movingtime) {
		if (collisionCheck(x + dx, y + dy)) {
			cnt = movingtime;
		}
		else {
			// constant direction moving
			imageLayer.images[imageidx].x += dx;
			imageLayer.images[imageidx].y += dy;

			x = imageLayer.images[imageidx].x;
			y = imageLayer.images[imageidx].y;
		}
	}

	if (cnt == movingtime) {
		makeFireground();
	}
	else if (cnt == movingtime + FIREGROUND_SEC) {
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
	// center is always true
	fireground[1][1] = true;
}

void CharizardFireball::makeFireground() {

	int startX = x - BLOCKSIZE;
	int startY = y - BLOCKSIZE;

	int curX, curY;

	// i is y and k is x
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {

			// if false dont check
			if (!fireground[i][k]) continue;

			curY = startY + BLOCKSIZE * i;
			curX = startX + BLOCKSIZE * k;

			// check range for outofbounds
			//if (curX < BLOCKSIZE || curX > 1200 - BLOCKSIZE || curY < BLOCKSIZE || curY > 1200 - BLOCKSIZE) continue;


			if (curX < AREA_ORIGIN_X + BLOCKSIZE || curX > AREA_ORIGIN_X + 1200 - BLOCKSIZE
				|| curY < AREA_ORIGIN_Y + BLOCKSIZE || curY > AREA_ORIGIN_Y + 1200 - BLOCKSIZE) continue;


			if (!collisionCheck(curX + dx, curY + dy)) {
				fireground_indexes.push_back(imageLayer.imageCount);
				imageArray[imageLayer.imageCount++] = { bmpNameFireground, curX, curY, 1 };
			}
		}
	}

	// always change the ceneter image to fireground image
	// else fireball image is left
	imageArray[imageidx].fileName = bmpNameFireground;
}

void CharizardFireball::eraseFireground() {

	// make all the firegrounds images NULL
	for (int i = 0; i < fireground_indexes.size(); i++) {
		imageArray[fireground_indexes[i]].fileName = bmpNameNull;
	}

	// make the fireball images NULL
	imageArray[imageidx].fileName = bmpNameNull;
}

#endif