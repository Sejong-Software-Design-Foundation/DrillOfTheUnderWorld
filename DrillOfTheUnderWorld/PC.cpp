#include "PC.hpp"
#include "common.hpp"
#include <string>

using namespace std;

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
std::vector<int> PC::getitemList() { return itemList; }
int PC::getStone() { return stone; }
int PC::getHP() { return HP; }
int PC::getOxygen() { return O2; }
int PC::getMaxHP() { return MAX_HP; }
int PC::getMaxOxygen() { return MAX_O2; }
int PC::getATK() { return ATK; }
void PC::setStone(int stone) { this->stone = stone; }
void PC::setHP(int hp) { 

	int prev_HP = this->HP / 10;
	if (hp <= 0) {
		this->HP = 0;
		exit(0);
	}
	else if (hp > MAX_HP) this->HP = MAX_HP;
	else this->HP = hp;
	int cur_HP = this->HP / 10;
	imageArray[index_Area_UI_HP_Start + prev_HP].isHide = 1;
	imageArray[index_Area_UI_HP_Start + cur_HP].isHide = 0;
}

void PC::setOxygen(int o2) {

	int prev_O2 = this->O2 / 10;
	if (o2 <= 0) {
		this->O2 = 0;
		pc.setHP(pc.getHP() - 1);
	}
	else if (o2 > MAX_O2) this->O2 = MAX_O2;
	else this->O2 = o2;
	int cur_O2 = this->O2 / 10;
	imageArray[index_Area_UI_O2_Start + prev_O2].isHide = 1;
	imageArray[index_Area_UI_O2_Start + cur_O2].isHide = 0;
}
void PC::setATK(int atk) { this->ATK = atk; }

void PC::dig(int x, int y) { // ������ �׸�
	if (!isDigable(x, y)) return;

	pc.vibe();
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0 || infoY >= 1200 || infoX < 0 || infoX >= 1200) return;
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			if (blockInfo[curY][curX]) 
				blockInfo[curY][curX] = blockInfo[curY][curX] - pc.getATK();
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * AREA_WIDTH + (infoX / BLOCKSIZE) + 1;

	if (!blockInfo[infoY][infoX]) {
		imageLayer.images[imageIndex].fileName = bmpNullName;
	}
	else if (blockInfo[infoY][infoX] == 1) {
		imageLayer.images[imageIndex].fileName = bmpBrokenStoneBlockName;
	}
	else if (blockInfo[infoY][infoX] == 3) {

		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameBronzeMineral;
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameSilverMineral;
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameGoldMineral;
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameDiamondMineral;
		}

		blockInfo[infoY][infoX] = 1;
	}
}
void PC::moveInStage() {
	stageLayer.images[0].x += dx[curDirection] * AREA_BLOCK_SIZE;
	stageLayer.images[0].y += dy[curDirection] * AREA_BLOCK_SIZE;
}

void PC::move() {
	imageLayer.images[0].x += dx[curDirection] * SPEED;
	imageLayer.images[0].y += dy[curDirection] * SPEED;
}

int PC::getDir() {
	return curDirection;
}

COORD PC::getPosAfterMove(int x, int y) {
	COORD result;
	result.X = x + dx[curDirection] * SPEED;
	result.Y = y + dy[curDirection] * SPEED;
	return result;
}
COORD PC::getTargetPos(int x, int y) {
	COORD result;
	result.X = x + dx[curDirection] * BLOCKSIZE;
	result.Y = y + dy[curDirection] * BLOCKSIZE;
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

int PC::getAtkLev() { return AtkLev; }
int PC::getAtkSpdLev() { return AtkSpdLev; }
int PC::getSpdLev() { return SpdLev; }
void PC::setAtkLev(int lev) {
	if (lev < 1) this->AtkLev = 1;
	else if (lev > 11) this->AtkLev = 11;
	else this->AtkLev = lev;
}
void PC::setAtkSpdLev(int lev) {
	if (lev < 1) this->AtkSpdLev = 1;
	else if (lev > 11) this->AtkSpdLev = 11;
	else this->AtkSpdLev = lev;
}
void PC::setSpdLev(int lev) {
	if (lev < 1) this->SpdLev = 1;
	else if (lev > 11) this->SpdLev = 11;
	else this->SpdLev = lev;
}

void PC::addItem(int itemIndex) {
	itemList.push_back(itemIndex);
}