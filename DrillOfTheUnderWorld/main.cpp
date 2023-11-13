#include "common.hpp"

int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);
	testLayer.initialize(&testLayer);

	char bmpNamePC[] = "PlayerCharacter.bmp";
	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 };
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;
	initBlockImages();

	char bmpNameTmp[] = "emptyTile.bmp";
	Image testImages[1] = { bmpNameTmp, 100, 100, 1 };

	testLayer.imageCount = 1;
	testLayer.images = testImages;

	targetLayer = &testLayer;
	targetLayer->renderAll(targetLayer);
	
	while (1) {
		while (_kbhit() != 0) {
			int key = _getch();
			int curPosX = imageLayer.images[0].x;
			int curPosY = imageLayer.images[0].y;
			COORD afterMovedPos;

			switch (key) {
			case S:
				targetLayer->fadeOut(targetLayer, NULL);
				if (isOnStage) {
					targetLayer = &imageLayer;
					isOnStage = false;
				}
				else {
					targetLayer = &testLayer;
					isOnStage = true;
				}
				targetLayer->fadeIn(targetLayer, NULL);
				break;
			case C:
				printf("%d", collisionCheck(curPosX, curPosY));
				break;
			case LEFT:
				pc.setDirLeft();
				afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
				if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
				break;
			case RIGHT:
				pc.setDirRight();
				afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
				if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
				break;
			case UP:
				pc.setDirUp();
				afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
				if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
				break;
;			case DOWN:
				pc.setDirDown();
				afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
				if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
				break;
			case ESC:
				return 0;
				break;
			case SPACE:
				COORD targetPos = pc.getTargetPos(curPosX, curPosY);
				pc.dig(targetPos.X, targetPos.Y);
				break;
			}
			if (key) targetLayer->renderAll(targetLayer);
		}
	}

	return 0;
}