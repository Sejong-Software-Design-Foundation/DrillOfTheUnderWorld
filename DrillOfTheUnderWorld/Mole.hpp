#ifndef __MOLE_
#define __MOLE_

#include "NPC.hpp"

/// <summary>
/// === MOLE INFO ===
/// HP : 50
/// AD : 15
/// MOVEMENT : NPCTRACKINGMOVEMENT
/// </summary>

class Mole : public NPC {
public:
    Mole(int x, int y);

    void move();
    void attack();
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	void dig(int x, int y);
	bool isDigable(int x, int y);
	int moveCnt = 0;
};

Mole::Mole(int x, int y) : NPC(x, y, 50, 15, rand() % 4) {
    this->imageidx = imageLayer.imageCount;
    imageArray[imageLayer.imageCount++] = { bmpNameMole, x, y, 1 };
}

void Mole::move() {
	if (collisionCheck(x + dx[curDirection] * BLOCKSIZE, y + dy[curDirection] * BLOCKSIZE)) {
		if (moveCnt == 0) {
			this->dig(x + dx[curDirection] * BLOCKSIZE, y + dy[curDirection] * BLOCKSIZE);
		}
	}
    NPCBossMovement();
	moveCnt = (moveCnt + 1) % 10;
}

void Mole::attack() {
    pc.setHP(pc.getHP() - attack_damage);
}

void Mole::dig(int x, int y) {
	if (!isDigable(x, y)) return;
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
				if (blockInfo[curY][curX]) blockInfo[curY][curX]--;
			}
		}
	}
	int imageIndex = (infoY / BLOCKSIZE) * AREA_WIDTH + (infoX / BLOCKSIZE) + 1;
	imageArray[imageidx].fileName = bmpNameMoleDigging;
	imageArray[imageIndex].fileName = bmpBrokenStoneBlockName;
	imageLayer.renderAll(&imageLayer);
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			if (blockInfo[curY][curX])
			{
				if (blockInfo[curY][curX]) blockInfo[curY][curX]--;
			}
		}
	}
	imageArray[imageIndex].fileName = bmpNameNull;
	imageArray[imageidx].fileName = bmpNameMole;
}

bool Mole::isDigable(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (blockInfo[infoY][infoX] > 2 || blockInfo[infoY][infoX] <= 0 || 
		strcmp(imageArray[(infoY / BLOCKSIZE) * AREA_WIDTH + (infoX / BLOCKSIZE) + 1].fileName, bmpFlagName) == 0) return false;
	else if (curDirection == 0 || curDirection == 2) return x % BLOCKSIZE == 0;
	else return y % BLOCKSIZE == 0;
	//return (x % BLOCKSIZE == 0 && y % BLOCKSIZE == 0);
}

#endif