#ifndef __CHARIZARD_FIREBALL_
#define __CHARIZARD_FIREBALL_

#define FIREGROUND_SEC 6

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

	int getDistance(int x1, int x2, int y1, int y2);
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

int CharizardFireball::getDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// check if PC is on Fireground of each Fireball
bool CharizardFireball::PCNear() {
	int PC_X = imageLayer.images[0].x;
	int PC_Y = imageLayer.images[0].y;

	// if two circles contact each other 
	for (int i = 0; i < fireground_indexes.size(); i++) {
		Image curground = imageArray[fireground_indexes[i]];
		// circle's center point
		int CENTER_X = curground.x - BLOCKSIZE / 2;
		int CENTER_Y = curground.y - BLOCKSIZE / 2;

		if (getDistance(PC_X, CENTER_X, PC_Y, CENTER_Y) < BLOCKSIZE) {
			return true;
		}
	}
	return false;
}

// this lives until eraseFireground
void CharizardFireball::move() {

	// check the 9 blocks of fireground area
	if (PCNear()) {
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
	// center is always 1
	fireground[1][1] = 1;
}

void CharizardFireball::makeFireground() {

	int startX = x - BLOCKSIZE;
	int startY = y - BLOCKSIZE;

	//int infoX = convertPosToInfoX(startX);
	//int infoY = convertPosToInfoY(startY);

	int curX, curY;

	// i is y and k is x
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {

			if (fireground[i][k] == 0) continue;
			curY = startY + BLOCKSIZE * i;
			curX = startX + BLOCKSIZE * k;

			// check range for outofbounds
			if (curX < BLOCKSIZE || curX > 1200 - BLOCKSIZE || curY < BLOCKSIZE || curY > 1200 - BLOCKSIZE) continue;

			for (int dy = 0; dy < BLOCKSIZE; dy++) {
				for (int dx = 0; dx < BLOCKSIZE; dx++) {
					if (blockInfo[convertPosToInfoY(curY + dy)][convertPosToInfoX(curX + dx)] != 0) {
						fireground[i][k] = 0;
						goto skip;
					}
				}
			}

		skip:
			if (fireground[i][k]) {
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