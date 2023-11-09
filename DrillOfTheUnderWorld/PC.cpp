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
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	blockInfo[infoY][infoX]--;
	if (!blockInfo[infoY][infoX]) {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = 0;
	}
	else {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = bmpBrokenStoneBlockName;
	}
}
