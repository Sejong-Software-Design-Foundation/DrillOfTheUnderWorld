#include "common.hpp"

int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);

	char bmpNamePC[] = "PlayerCharacter.bmp";
	char bmpNameBackground[] = "basicStoneBlocks.bmp";
	imageArray[0] = { bmpNamePC, 48, 48, 1 };
	imageArray[1] = { bmpNameBackground, 0, 96, 1 };
	initBlockInfo();

	imageLayer.imageCount = 2;

	imageLayer.images = imageArray;
	imageLayer.renderAll(&imageLayer);

	while (1) {
		while (_kbhit() != 0) {
			int key = _getch();
			int curPosX = imageLayer.images[0].x;
			int curPosY = imageLayer.images[0].y;

			switch (key) {
			case S:
				break;
			case LEFT:
				if (collisionCheck(curPosX - BLOCKSIZE, curPosY)) dig(curPosX-BLOCKSIZE, curPosY);
				else imageLayer.images[0].x-= BLOCKSIZE;
				break;
			case RIGHT:
				if (collisionCheck(curPosX + BLOCKSIZE, curPosY)) dig(curPosX+ BLOCKSIZE, curPosY);
				else imageLayer.images[0].x+= BLOCKSIZE;
				break;
			case UP:
				if (collisionCheck(curPosX, curPosY - BLOCKSIZE)) dig(curPosX, curPosY- BLOCKSIZE);
				else imageLayer.images[0].y -= BLOCKSIZE;
				break;
			case DOWN:
				if (collisionCheck(curPosX, curPosY + BLOCKSIZE)) dig(curPosX, curPosY+BLOCKSIZE);
				else imageLayer.images[0].y += BLOCKSIZE;
				break;
			case ESC:
				return 0;
				break;
			}
			if (key) imageLayer.renderAll(&imageLayer);	
		}
	}

	return 0;
}