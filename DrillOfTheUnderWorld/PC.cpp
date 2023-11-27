#include "PC.hpp"
#include "common.hpp"
#include <string>

using namespace std;
/*
PC 능력치 로직
팅기는 버그 해결

*/
PC& PC::getPC() {
	static PC pc;
	return pc;
}

void PC::vibe() {
	if (curDirection == 0) {
		imageLayer.images[0].x -= 8;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].x += 16;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].x -= 8;
		imageLayer.renderAll(&imageLayer);
	}
	else if (curDirection == 2) {
		imageLayer.images[0].x += 8;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].x -= 16;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].x += 8;
		imageLayer.renderAll(&imageLayer);
	}
	else if (curDirection == 3) {
		imageLayer.images[0].y += 8;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].y -= 16;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].y += 8;
		imageLayer.renderAll(&imageLayer);
	}
	else {
		imageLayer.images[0].y -= 8;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].y += 16;
		imageLayer.renderAll(&imageLayer);
		imageLayer.images[0].y -= 8;
		imageLayer.renderAll(&imageLayer);
	}
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

void PC::dig(int x, int y) { 
	if (!isDigable(x, y)) return;
	pc.vibe();
	if (x % BLOCKSIZE > BLOCKSIZE / 2) x = x - x % BLOCKSIZE + BLOCKSIZE;
	else x = x - x % BLOCKSIZE;
	if (y % BLOCKSIZE > BLOCKSIZE / 2) y = y - y % BLOCKSIZE + BLOCKSIZE;
	else y = y - y % BLOCKSIZE;
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0 || infoY >= 1200 || infoX < 0 || infoX >= 1200) return;
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			if (blockInfo[curY][curX])
				blockInfo[curY][curX] = blockInfo[curY][curX] - pc.getAtkLev();
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * AREA_WIDTH + (infoX / BLOCKSIZE) + 1;
	updateDigResultReward(y, x, infoY, infoX, imageIndex);
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

bool PC::isDigable(int x, int y) {
	if (curDirection == 0 || curDirection == 2) return x % BLOCKSIZE == 0;
	else return y % BLOCKSIZE == 0;
	//return (x % BLOCKSIZE == 0 && y % BLOCKSIZE == 0);
}
void PC::applyDigReward(int targerImageIndex, int delay) {
	// step1 move target reward image to PC top postion and reward value
	targetLayer->renderAll(targetLayer);
	Sleep(delay);

	int currentPcPosX = imageArray[0].x;
	int currentPcPosY = imageArray[0].y;
	int targetPosX = currentPcPosX;
	int targetPosY = currentPcPosY - BLOCKSIZE;

	//imageArray[targerImageIndex].scale = 2;
	imageArray[targerImageIndex].x = targetPosX;
	imageArray[targerImageIndex].y = targetPosY;

	targetLayer->renderAll(targetLayer);
	Sleep(delay);

	if (strcmp(imageArray[targerImageIndex].fileName, bmpNameBronzeMineral) == 0) {
		pc.setStone(pc.getStone() + 10);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameSilverMineral) == 0) {
		pc.setStone(pc.getStone() + 30);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameGoldMineral) == 0) {
		pc.setStone(pc.getStone() + 50);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameDiamondMineral) == 0) {
		pc.setStone(pc.getStone() + 100);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpHpPotionName) == 0) {
		pc.setHP(pc.getHP() + (pc.getMaxHP() * 0.3));
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpOzPotionName) == 0) {
		pc.setOxygen(pc.getOxygen() + (pc.getMaxOxygen() * 0.3));
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameOrichalcumMineral) == 0) {
		pc.setStone(pc.getStone() + 1000);
	}

	imageArray[targerImageIndex].fileName = bmpNullName;
}

void PC::updateDigResultReward(int digY, int digX, int infoY, int infoX, int imageIndex) {
	if (blockInfo[infoY][infoX] <= 0) {
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpStoneBlockName) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpBrokenStoneBlockName) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNullName;
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre1) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenBronzeOre) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameBronzeMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre1) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenSilverOre) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameSilverMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre1) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenGoldOre) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameGoldMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre1) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenDiamondOre) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameDiamondMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameOrichalcumOre1) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameOrichalcumOre2) == 0)) {
			OrichalcumNum++;
			if (OrichalcumNum >= 5) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar1;
			if (OrichalcumNum >= 10) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar2;
			if (OrichalcumNum >= 20) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar3;
			imageLayer.images[imageIndex].fileName = bmpNameOrichalcumMineral;
			applyDigReward(imageIndex, 300);
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpQuestionMarkName) == 0) {
			digQuestionBlock(digY, digX, infoY, infoX, imageIndex);
		}
	}
	// 나중에 매직넘버 처리하기 -> 광물 HP
	if (blockInfo[infoY][infoX] <= 1) { // bronze -> 3
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpStoneBlockName) == 0) {
			imageLayer.images[imageIndex].fileName = bmpBrokenStoneBlockName;
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre1) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenBronzeOre;
		}
	}
	if (blockInfo[infoY][infoX] <= 3) { // silver -> 6
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre1) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenSilverOre;
		}
	}
	if (blockInfo[infoY][infoX] <= 4) { // gold -> 9
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre1) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenGoldOre;
		}
	}
	if (blockInfo[infoY][infoX] <= 6) { // diamond -> 12 
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre1) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenDiamondOre;
		}
	}
}

void PC::digQuestionBlock(int digY, int digX, int infoY, int infoX, int imageIndex) {
	srand(static_cast<unsigned int>(time(nullptr)));

	int questionResult = rand() % 4;
	switch (questionResult)
	{
	case 0:
		imageLayer.images[imageIndex].fileName = bmpHpPotionName;
		applyDigReward(imageIndex, 300);
		break;
	case 1:
		imageLayer.images[imageIndex].fileName = bmpOzPotionName;
		applyDigReward(imageIndex, 300);
		break;
	case 2:
		imageLayer.images[imageIndex].fileName = bmpBoomName;
		targetLayer->renderAll(targetLayer);
		Sleep(200);
		boom(digY, digX, infoY, infoX, imageIndex);
		break;
	case 3:
		imageLayer.images[imageIndex].fileName = bmpNullName;
		isGenerateMobByQuestionBlock = true;
		questionBlockPosX = digX;
		questionBlockPosY = digY;
		break;
	default:
		break;
	}

}

void PC::boom(int digY, int digX, int infoY, int infoX, int imageIndex) {
	std::vector<int> rewardImageIndexList;
	// set blockinfo

	for (int row = infoY - BLOCKSIZE; row <= infoY + BLOCKSIZE * 2; row++) {
		if (row < 0 || row >= 1200) continue;
		for (int col = infoX - BLOCKSIZE; col <= infoX + BLOCKSIZE * 2; col++) {
			if (col < 0 || col >= 1200) continue;
			if (blockInfo[row][col]) blockInfo[row][col] = 0;
		}
	}


	for (int row = infoY - BLOCKSIZE; row < infoY + BLOCKSIZE * 2; row += BLOCKSIZE) {
		if (row < 0 || row >= 1200) continue;
		for (int col = infoX - BLOCKSIZE; col < infoX + BLOCKSIZE * 2; col += BLOCKSIZE) {
			if (col < 0 || col >= 1200) continue;

			int targetImageIndex = (row / BLOCKSIZE) * AREA_WIDTH + (col / BLOCKSIZE) + 1;

			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpStoneBlockName) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpBrokenStoneBlockName) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNullName;
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBronzeOre1) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenBronzeOre) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameBronzeMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameSilverOre1) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenSilverOre) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameSilverMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameGoldOre1) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenGoldOre) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameGoldMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameDiamondOre1) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenDiamondOre) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameDiamondMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameOrichalcumMineral) == 0) {
				OrichalcumNum++;
				if (OrichalcumNum >= 5) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar1;
				if (OrichalcumNum >= 10) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar2;
				if (OrichalcumNum >= 20) imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar3;
			}
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpBoomName) == 0) {
				imageLayer.images[targetImageIndex].fileName = bmpNullName;
			}
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpQuestionMarkName) == 0) {
				digQuestionBlock(digY, digX, row, col, targetImageIndex);
			}
		}
	}

	if (!rewardImageIndexList.empty()) {
		for (int imageIndex : rewardImageIndexList) {
			applyDigReward(imageIndex, 100);
		}
	}
	//boom
}