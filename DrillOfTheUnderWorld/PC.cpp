#include "PC.hpp"
#include <string>
#include "Item.hpp"
#include "common.hpp"
#include "itemCommon.hpp"
#include <thread>

using namespace std;

 char PCBullet::bmpPCBulletLeftName[] = "PCBullet_left.bmp";
 char PCBullet::bmpPCBulletRightName[] = "PCBullet_right.bmp";
 char PCBullet::bmpPCBulletUpName[] = "PCBullet_up.bmp";
 char PCBullet::bmpPCBulletDownName[] = "PCBullet_down.bmp";

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
int PC::getFatigue() { return FATIGUE; }
int PC::getMaxHP() { return MAX_HP; }
int PC::getMaxOxygen() { return MAX_O2; }
int PC::getMaxFatigue() { return MAX_FATIGUE; }
int PC::getATK() { return ATK; }
void PC::setStone(int stone) { this->stone = stone; updateCharacterStatus();
}
void PC::setHP(int hp) {
	if (hp < HP) { 
		clock_t curTime = clock();
		if (curTime - lastHitTime < 1000) return; //1ÃÊ ÀÌ³»¿¡ ´Ù½Ã ¸ÂÀ¸¸é ¾È¸Â°ÔÇÔ
		lastHitTime = curTime;
		hitEffect();
	}
	else if (hp > HP) getHPEffect();

	int prev_HP = this->HP / (this->MAX_HP / 10);
	if (hp <= 0) {
		this->HP = 0;
		// item
		if (this->hasLuckCharm) {
			this->HP = this->MAX_HP;
			this->hasLuckCharm = false;

			for (auto iter = ownedItems.begin(); iter != ownedItems.end(); ) {
				if (auto luckCharm = dynamic_cast<LuckyCharm*>(*iter)) {
					iter = ownedItems.erase(iter);
					delete luckCharm; 
				}
				else {
					++iter;
				}
			}
			updateCharacterStatus();
		}
		else {
			// die
			//printGameOver();
		}
	}
	else if (hp > MAX_HP) this->HP = MAX_HP;
	else this->HP = hp;
	int cur_HP = this->HP / (this->MAX_HP / 10);
;	uiImageArray[index_Area_UI_HP_Start + prev_HP].isHide = 1;
	uiImageArray[index_Area_UI_HP_Start + cur_HP].isHide = 0;
	updateCharacterStatus();
}

void PC::setOxygen(int o2) {
	if (o2 < O2);
	else if (o2 > O2) getOxygenEffect();

	int prev_O2 = this->O2 / (this->MAX_O2 / 10);
	if (o2 <= 0) {
		this->O2 = 0;
		pc.setHP(pc.getHP() - 1);
	}
	else if (o2 > MAX_O2) this->O2 = MAX_O2;
	else this->O2 = o2;
	int cur_O2 = this->O2 / (this->MAX_O2 / 10);
	uiImageArray[index_Area_UI_O2_Start + prev_O2].isHide = 1;
	uiImageArray[index_Area_UI_O2_Start + cur_O2].isHide = 0;
	updateCharacterStatus();
}

void PC::setFatigue(int ft) {
	this->FATIGUE = ft;
	if (this->FATIGUE <= 0) printGameOver();
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
			{
				blockInfo[curY][curX] = blockInfo[curY][curX] - pc.getAtkLev();
				if (blockInfo[curY][curX] < 0) blockInfo[curY][curX] = 0;
			}
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
	if (isBossArea) { 
		imageLayer.images[0].x += dx[curDirection] * SPEED/2 + (dx[curDirection] * SPEED * SpdLev) / 10;
		imageLayer.images[0].y += dy[curDirection] * SPEED/2 + (dy[curDirection] * SPEED * SpdLev) / 10;
	}
	else {
		imageLayer.images[0].x += dx[curDirection] * SPEED;
		imageLayer.images[0].y += dy[curDirection] * SPEED;
	}
}

int PC::getDir() {
	return curDirection;
}

COORD PC::getPosAfterMove(int x, int y) {
	COORD result;
	if (isBossArea) {
		result.X = x + dx[curDirection] * SPEED / 2 + (dx[curDirection] * SPEED * SpdLev) / 10;
		result.Y = y + dy[curDirection] * SPEED / 2 + (dy[curDirection] * SPEED * SpdLev) / 10;
	}
	else {
		result.X = x + dx[curDirection] * SPEED;
		result.Y = y + dy[curDirection] * SPEED;
	}
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

	//imageArray[targerImageIndex].scale = 2;w
	imageArray[targerImageIndex].x = targetPosX;
	imageArray[targerImageIndex].y = targetPosY;

	targetLayer->renderAll(targetLayer);
	Sleep(delay);

	int rewardStone = 0;

	if (strcmp(imageArray[targerImageIndex].fileName, bmpNameBronzeMineral) == 0) {
		rewardStone = 10;
		if (hasMoleClaw) {
			rewardStone *= 2;
		}
		pc.setStone(pc.getStone() + rewardStone);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameSilverMineral) == 0) {
		rewardStone = 30;
		if (hasMoleClaw) {
			rewardStone *= 2;
		}
		pc.setStone(pc.getStone() + rewardStone);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameGoldMineral) == 0) {
		rewardStone = 50;
		if (hasMoleClaw) {
			rewardStone *= 2;
		}
		pc.setStone(pc.getStone() + rewardStone);
	}
	else if (strcmp(imageArray[targerImageIndex].fileName, bmpNameDiamondMineral) == 0) {
		rewardStone = 100;
		if (hasMoleClaw) {
			rewardStone *= 2;
		}
		pc.setStone(pc.getStone() + rewardStone);
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

	imageArray[targerImageIndex].fileName = bmpNameNull;
}

void PC::increaseFlagCnt() {
	flagCnt++;
	drawProgress();
	printFlagStageStatus(pc.getFlagCnt());

	//imageArray[imageLayer.imageCount++] = { bmpFlagName, AREA_ORIGIN_X + BLOCKSIZE * 25 + 100 + flagCnt * BLOCKSIZE * 2,BLOCKSIZE * 13,2 };
}
void PC::initFlagCnt() {
	flagCnt = 0;
	//imageArray[imageLayer.imageCount] = { bmpFlagName, AREA_ORIGIN_X + BLOCKSIZE * 25 + 100 + flagCnt * BLOCKSIZE * 2,BLOCKSIZE * 13,2 };
}
int PC::getFlagCnt() {
	return flagCnt;
}


void PC::updateDigResultReward(int digY, int digX, int infoY, int infoX, int imageIndex) {
	if (blockInfo[infoY][infoX] <= 0) {
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpStoneBlockName[stageLevel-1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpBrokenStoneBlockName[stageLevel-1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameNull;
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenBronzeOre[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameBronzeMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenSilverOre[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameSilverMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenGoldOre[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameGoldMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBrokenDiamondOre[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameDiamondMineral;
			applyDigReward(imageIndex, 300);
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameOrichalcumOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameOrichalcumOre2[stageLevel - 1]) == 0)) {
			OrichalcumNum++;
			drawProgress();
			if (OrichalcumNum >= 3) progressImageArray[29].fileName = bmpNameStar1;
			if (OrichalcumNum >= 6) progressImageArray[29].fileName = bmpNameStar2;
			if (OrichalcumNum >= 10) progressImageArray[29].fileName = bmpNameStar3;
			imageLayer.images[imageIndex].fileName = bmpNameOrichalcumMineral;
			applyDigReward(imageIndex, 300);
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpQuestionMarkName) == 0) {
			digQuestionBlock(digY, digX, infoY, infoX, imageIndex);
		}
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpFlagName) == 0) {
			imageLayer.images[imageIndex].fileName = bmpNameNull;
			increaseFlagCnt();
			applyDigReward(imageIndex, 300);
		}
	}
	// ??Ã¬Â¤???Ã«Â§Â¤Ã¬Â§Â??Ã«Â²??Ã¬Â²?Ã«Â¦Â¬??ÃªÂ¸Â° -> ÃªÂ´?˜Ã«Â??HP
	if (blockInfo[infoY][infoX] <= 1) { // bronze -> 3
		if (strcmp(imageLayer.images[imageIndex].fileName, bmpStoneBlockName[stageLevel - 1]) == 0) {
			imageLayer.images[imageIndex].fileName = bmpBrokenStoneBlockName[stageLevel - 1];
		}
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameBronzeOre2[stageLevel - 1]) == 0)){
			imageLayer.images[imageIndex].fileName = bmpNameBrokenBronzeOre[stageLevel - 1];
		}
	}
	if (blockInfo[infoY][infoX] <= 3) { // silver -> 6
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameSilverOre2[stageLevel - 1]) == 0)){
			imageLayer.images[imageIndex].fileName = bmpNameBrokenSilverOre[stageLevel - 1];
		}
	}
	if (blockInfo[infoY][infoX] <= 4) { // gold -> 9
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameGoldOre2[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenGoldOre[stageLevel - 1];
		}
	}
	if (blockInfo[infoY][infoX] <= 6) { // diamond -> 12 
		if ((strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[imageIndex].fileName, bmpNameDiamondOre2[stageLevel - 1]) == 0)) {
			imageLayer.images[imageIndex].fileName = bmpNameBrokenDiamondOre[stageLevel - 1];
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
		imageLayer.images[imageIndex].fileName = bmpNameNull;
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
			int targetImageIndex = (row / BLOCKSIZE) * AREA_WIDTH + (col / BLOCKSIZE) + 1;
			if (col < 0 || col >= 1200) continue;
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpBedrockName) == 0) continue;
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpFlagName) == 0) continue;
			if (blockInfo[row][col]) blockInfo[row][col] = 0;
		}
	}


	for (int row = infoY - BLOCKSIZE; row < infoY + BLOCKSIZE * 2; row += BLOCKSIZE) {
		if (row < 0 || row >= 1200) continue;
		for (int col = infoX - BLOCKSIZE; col < infoX + BLOCKSIZE * 2; col += BLOCKSIZE) {
			if (col < 0 || col >= 1200) continue;

			int targetImageIndex = (row / BLOCKSIZE) * AREA_WIDTH + (col / BLOCKSIZE) + 1;

			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpStoneBlockName[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpBrokenStoneBlockName[stageLevel - 1]) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameNull;
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBronzeOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBronzeOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenBronzeOre[stageLevel - 1]) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameBronzeMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameSilverOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameSilverOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenSilverOre[stageLevel - 1]) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameSilverMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameGoldOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameGoldOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenGoldOre[stageLevel - 1]) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameGoldMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if ((strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameDiamondOre1[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameDiamondOre2[stageLevel - 1]) == 0) || (strcmp(imageLayer.images[targetImageIndex].fileName, bmpNameBrokenDiamondOre[stageLevel - 1]) == 0)) {
				imageLayer.images[targetImageIndex].fileName = bmpNameDiamondMineral;
				rewardImageIndexList.push_back(targetImageIndex);
			}
			if (strcmp(imageLayer.images[targetImageIndex].fileName, bmpBoomName) == 0) {
				imageLayer.images[targetImageIndex].fileName = bmpNameNull;
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

void PC::hitEffect() {
	char* bmpNameForHitEffect = 0;
	char* bmpCurName = imageArray[0].fileName;
	switch (this->curDirection) {
	case 0: bmpNameForHitEffect = bmpPCHitRightName; break;
	case 1: bmpNameForHitEffect = bmpPCHitDownName; break;
	case 2: bmpNameForHitEffect = bmpPCHitLeftName; break;
	case 3: bmpNameForHitEffect = bmpPCHitUpName; break;
	}
	imageArray[0].fileName = bmpNameForHitEffect;
	targetLayer->renderAll(targetLayer);
	imageArray[0].fileName = bmpCurName;
	targetLayer->renderAll(targetLayer);
}

void PC::getHPEffect() {
	char* bmpNameForEffect = 0;
	char* bmpCurName = imageArray[0].fileName;
	switch (this->curDirection) {
	case 0: bmpNameForEffect = bmpPCgetHPRightName; break;
	case 1: bmpNameForEffect = bmpPCgetHPDownName; break;
	case 2: bmpNameForEffect = bmpPCgetHPLeftName; break;
	case 3: bmpNameForEffect = bmpPCgetHPUpName; break;
	}
	imageArray[0].fileName = bmpNameForEffect;
	targetLayer->renderAll(targetLayer);
	imageArray[0].fileName = bmpCurName;
	targetLayer->renderAll(targetLayer);
}

void PC::getOxygenEffect() {
	char* bmpNameForEffect = 0;
	char* bmpCurName = imageArray[0].fileName;
	switch (this->curDirection) {
	case 0: bmpNameForEffect = bmpPCgetOxygenRightName; break;
	case 1: bmpNameForEffect = bmpPCgetOxygenDownName; break;
	case 2: bmpNameForEffect = bmpPCgetOxygenLeftName; break;
	case 3: bmpNameForEffect = bmpPCgetOxygenUpName; break;
	}
	imageArray[0].fileName = bmpNameForEffect;
	targetLayer->renderAll(targetLayer);
	imageArray[0].fileName = bmpCurName;
	targetLayer->renderAll(targetLayer);
}


void PC::setMaxHP(int maxHp) {
	if (maxHp > 0) {
		this->MAX_HP = maxHp;
	}
}
void PC::setMaxOxygen(int maxOxygen) {
	if (maxOxygen > 0) {
		this->MAX_O2 = maxOxygen;
	}
}
void PC::setMaxFatigue(int maxFt) {
	if (maxFt > 0) {
		this->MAX_FATIGUE = maxFt;
	}
}
/*
std::vector<Item*> PC::getOwnedItemList() {
	return this->ownedItemList;
 }
*/

void PC::setUsableEnergyBarCount(int count) {
	this->usableEnergyBarCount = count;
	if (count == 0) {
		uiImageArray[index_Potion_Image].fileName = bmpNameNull;
	}
	else{
		uiImageArray[index_Potion_Image].fileName = bmpEnergyBarName;
	}
	this->usablePortableOxygenCanCount = 0;
}

void PC::setUsablePortableOxygenCanCount(int count) {
	this->usablePortableOxygenCanCount = count;
	if (count == 0) {
		uiImageArray[index_Potion_Image].fileName = bmpNameNull;
	}
	else {
		uiImageArray[index_Potion_Image].fileName = bmpPortableOxygenCanName;
	}
	this->usableEnergyBarCount = 0;
}
int PC::getUsableEnergyBarCount() {
	return this->usableEnergyBarCount;
}
int PC::getUsablePortableOxygenCanCount() {
	return this->usablePortableOxygenCanCount;
}


void PC::setHasBatFang(boolean isHas) {
	this->hasBatFang = isHas;
}

bool PC::getHasBatFang() {
	return this->hasBatFang;
}

void PC::setHashasBeggarDoll(boolean isHas) {
	this->hasBeggarDoll = isHas;
}
bool PC::getHashasBeggarDoll() {
	return this->hasBeggarDoll;
}
void PC::setHasLuckStone(boolean isHas) {
	this->hasLuckStone = isHas;
}
bool PC::getHasLuckStone() {
	return this->hasLuckStone;
}
void PC::setHasLuckCharm(boolean isHas) {
	this->hasLuckCharm = isHas;
}
bool PC::getHasLuckCharm() {
	return this->hasLuckCharm;
}
void PC::setLuckStoneStage(int luckStoneStage) {
	this->luckStoneStage = luckStoneStage;
}
int PC::getLuckStoneStage() {
	return this->luckStoneStage;
}
void PC::setHasMetalDetector(boolean isHas) {
	this->hasMetalDetector = isHas;
}
bool PC::getHasMetalDetector() {
	return this->hasMetalDetector;
}
void PC::setHasMoleClaw(boolean isHas) {
	this->hasMoleClaw = isHas;
}
bool PC::getMoleClaw() {
	return this->hasMoleClaw;
}
void PC::setHasThronCrown(boolean isHas) {
	this->hasThronCrown = isHas;
}
bool PC::getHasThronCrown() {
	return this->hasThronCrown;
}
void PC::setHasTwoHearts(boolean isHas) {
	this->hasTwoHearts = isHas;
}
bool PC::getHasTwoHearts() {
	return this->hasTwoHearts;
}
void PC::setHasUndergroundTicket(boolean isHas) {
	this->hasUndergroundTicket = isHas;
}
bool PC::getHasUndergroundTicket() {
	return this->hasUndergroundTicket;
}

void PC::attack(clock_t t) {
	int attackSpeed = AtkSpdLev;
	
	if (pc.hasBeggarDoll) { // speed up but use stone 
		attackSpeed *= 2;
	}

	if ((t - this->lastAttackTime) < 1000/ attackSpeed) return;
	if (pc.hasBeggarDoll) { // use stone 
		pc.setStone(pc.getStone() - 1);
	}
	pcBullets.push_back(PCBullet(imageArray[0].x, imageArray[0].y, this->curDirection));
	lastAttackTime = t;
}

PCBullet::PCBullet() {
	x = imageArray[0].x;
	y = imageArray[0].y;
	dir = pc.getDir();
	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameFireball, x, y, 1 };
}
PCBullet::PCBullet(int x, int y, int dir) {
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->imageidx = imageLayer.imageCount;
	switch (dir) {
	case 0:
		imageArray[imageLayer.imageCount++] = { bmpPCBulletRightName, x, y, 1 }; break;
	case 1:
		imageArray[imageLayer.imageCount++] = { bmpPCBulletDownName, x, y, 1 }; break;
	case 2:
		imageArray[imageLayer.imageCount++] = { bmpPCBulletLeftName, x, y, 1 }; break;
	case 3:
		imageArray[imageLayer.imageCount++] = { bmpPCBulletUpName, x, y, 1 }; break;
	default :
		imageArray[imageLayer.imageCount++] = { bmpPCBulletUpName, x, y, 1 }; break;
	}
}
bool PCBullet::move() {
	if (collisionCheck(x + dx[dir]*speed, y + dy[dir]*speed)) {
		imageLayer.images[imageidx].fileName = bmpNameNull;
		return false;
	}

	// update bullet position
	imageLayer.images[imageidx].x += dx[dir]*speed;
	imageLayer.images[imageidx].y += dy[dir]*speed;

	x = imageLayer.images[imageidx].x;
	y = imageLayer.images[imageidx].y;
	return true;
}

std::vector<PCBullet>& PC::getBulletList() {
	return pcBullets;
}

bool PCBullet::checkBulletHit(int bossX, int bossY) {
	if (x + BLOCKSIZE >= bossX && x <= bossX + BLOCKSIZE * BOSS_SCALE && y + BLOCKSIZE >= bossY && y < bossY + BLOCKSIZE * BOSS_SCALE) {
		imageLayer.images[imageidx].fileName = bmpNameNull;
		return true;
	}
	/*for (int dy = 0; dy < BLOCKSIZE;dy++) {
		for (int dx = 0;dx < BLOCKSIZE;dx++) {
			if (bossX == this->x + dx && bossY == this->y + dy) {
				imageLayer.images[imageidx].fileName = bmpNameNull;
				return true;
			}
		}
	}*/
	return false;
}

void PC::setLastAttackTime(clock_t t) {
	lastAttackTime = t;

}