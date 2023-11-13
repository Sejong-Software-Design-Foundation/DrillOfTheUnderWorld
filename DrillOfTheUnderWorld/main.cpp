#include "common.hpp"
int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);
	stageLayer.initialize(&stageLayer);

	char bmpNamePC[] = "PlayerCharacter.bmp";
	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initBlockImages();

	char bmpNameTmp[] = "emptyTile.bmp";

	/*
	Stage stage;
	std::vector<std::vector<Area>> areaList = stage.getAreaList();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d\n", areaList[i][j].getPosX());
		}
	}
	*/

	char bmpStageLevel[] = "Stage1.bmp";

	stageLayer.imageCount = STAGE_EXTRA_IMAGE_COUNT;
	initStageImages();
	stageLayer.images = stageImages;	
	stageLayer.images[0] = { bmpNamePC, STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 2 + 48
										, STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 2 + 48, 1 };
	stageLayer.images[1] = { bmpCharacterStatueName, 60 , STAGE_ORIGIN_Y, 1 };
	stageLayer.images[2] = { bmpStageLevel, STAGE_ORIGIN_X + AREA_BLOCK_SIZE + 48, 48, 0.2};

	stageLayer.images[(2) * 5 + 2 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;

	stageLayer.imageCount = 30;
	targetLayer = &stageLayer;

	targetLayer->renderAll(targetLayer);

	while (1) {
		if (isOnStage) {
			while (_kbhit() != 0) {
				int key = _getch();
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;
				switch (key) {
				case S:
					if (isOnStage) {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &imageLayer;
						isOnStage = false;
						currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
						currentAreaColIndex = convertPosToInfoXInStage(curPosX);

						imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
						imageLayer.images = imageArray;
						imageLayer.imageCount = 1;

						initBlockImages();

						targetLayer->fadeIn(targetLayer, NULL);
					}
					else {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &stageLayer;
						isOnStage = true;
						targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
						stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
						targetLayer->fadeIn(targetLayer, NULL);
					}
					break;

				case LEFT:
					pc.setDirLeft();
					if (!collisionCheckInStage(curPosX - AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheckInStage(curPosX + AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheckInStage(curPosX, curPosY - AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheckInStage(curPosX, curPosY + AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				}
				if (key) targetLayer->renderAll(targetLayer);
			}
		}
		else {
			while (_kbhit() != 0) {
				int key = _getch();
				int curPosX = imageLayer.images[0].x;
				int curPosY = imageLayer.images[0].y;

				switch (key) {
				case S:
					if (isOnStage) {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &imageLayer;
						isOnStage = false;
						currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
						currentAreaColIndex = convertPosToInfoXInStage(curPosX);

						imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
						imageLayer.images = imageArray;
						imageLayer.imageCount = 1;

						initBlockImages();

						targetLayer->fadeIn(targetLayer, NULL);
					}
					else {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &stageLayer;
						isOnStage = true;
						targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
						stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
						setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
						targetLayer->fadeIn(targetLayer, NULL);
					}
					break;
				case LEFT:
					pc.setDirLeft();
					if (!collisionCheck(curPosX - BLOCKSIZE, curPosY)) pc.move();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheck(curPosX + BLOCKSIZE, curPosY)) pc.move();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheck(curPosX, curPosY - BLOCKSIZE)) pc.move();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheck(curPosX, curPosY + BLOCKSIZE)) pc.move();
					break;
				case ESC:
					return 0;
					break;
				case SPACE:
					COORD posAfterMoved = pc.getPosAfterMove(curPosX, curPosY);
					pc.dig(posAfterMoved.X, posAfterMoved.Y);
				}
				if (key) targetLayer->renderAll(targetLayer);
			}
		}
	}

	return 0;
}