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
int PC::getStone() { return stone; }
int PC::getHP() { return HP; }
int PC::getOxygen() { return O_2; }
int PC::getATK() { return ATK; }
void PC::setStone(int stone) { this->stone = stone; }
void PC::setHP(int hp) { this->HP = hp; }
void PC::setOxygen(int o2) { this->O_2 = o2; }
void PC::setATK(int atk) { this->ATK = atk; }
void PC::dig(int x, int y) {
	pc.vibe();
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	if (blockInfo[infoY][infoX])
		blockInfo[infoY][infoX]--;
	if (!blockInfo[infoY][infoX]) {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = 0;
	}
	else {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = bmpBrokenStoneBlockName;
	}
}
void PC::moveInStage() {
	stageLayer.images[0].x += dir[curDirection][0] * AREA_BLOCK_SIZE;
	stageLayer.images[0].y += dir[curDirection][1] * AREA_BLOCK_SIZE;
}

void PC::move() {
	imageLayer.images[0].x += dir[curDirection][0]*BLOCKSIZE;
	imageLayer.images[0].y += dir[curDirection][1]*BLOCKSIZE;
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
	targetLayer->images[0].fileName = bmpPCRightName;
}
void PC::setDirLeft() {
	curDirection = 2;
	targetLayer->images[0].fileName = bmpPCLeftName;
}
void PC::setDirDown() {
	curDirection = 1;
	targetLayer->images[0].fileName = bmpPCDownName;
}
void PC::setDirUp() {
	curDirection = 3;
	targetLayer->images[0].fileName = bmpPCUpName;
}