#include "PC.hpp"
#include "common.hpp"

PC& PC::getPC() {
	static PC pc;
	return pc;
}
void PC::vibe() {
	imageLayer.images[0].x += 8;
	imageLayer.renderAll(&imageLayer);
	imageLayer.images[0].x -= 16;
	imageLayer.renderAll(&imageLayer);
	imageLayer.images[0].x += 8;
	imageLayer.renderAll(&imageLayer);
}
COORD PC::getCurPos() {
	COORD CurPos = { imageLayer.images[0].x, imageLayer.images[0].y };
	return CurPos;
}
int PC::getHP() { return HP; }
int PC::getOxygen() { return O_2; }
int PC::getATK() { return ATK; }
void PC::setHP(int hp) { this->HP = hp; }
void PC::setOxygen(int o2) { this->O_2 = o2; }
void PC::setATK(int atk) { this->ATK = atk; }
void PC::dig(int x, int y) {
	pc.vibe();
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (((x - AREA_ORIGIN_X) % BLOCKSIZE) > (BLOCKSIZE / 2)) infoX++;
	if (((y - AREA_ORIGIN_Y) % BLOCKSIZE) > (BLOCKSIZE / 2)) infoY++;
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	blockInfo[infoY][infoX]--;
	if (!blockInfo[infoY][infoX]) {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = 0;
	}
	else if (blockInfo[infoY][infoX]==1) {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = bmpBrokenStoneBlockName;
	}
}

void PC::move() {
	imageLayer.images[0].x += dir[curDirection][0]*SPEED;
	imageLayer.images[0].y += dir[curDirection][1]*SPEED;
}
int PC::getDir() {
	return curDirection;
}

COORD PC::getPosAfterMove(int x, int y) {
	COORD result;
	result.X = x + dir[curDirection][0]*BLOCKSIZE;
	result.Y = y + dir[curDirection][1]*BLOCKSIZE;
	return result;
}

void PC::setDirRight() {
	curDirection = 0;
	imageLayer.images[0].fileName = bmpPCRightName;
}
void PC::setDirLeft() {
	curDirection = 2;
	imageLayer.images[0].fileName = bmpPCLeftName;
}
void PC::setDirDown() {
	curDirection = 1;
	imageLayer.images[0].fileName = bmpPCDownName;
}
void PC::setDirUp() {
	curDirection = 3;
	imageLayer.images[0].fileName = bmpPCUpName;
}